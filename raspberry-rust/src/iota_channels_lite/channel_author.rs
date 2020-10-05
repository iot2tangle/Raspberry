//!
//! Channel author
//!
use crate::iota_channels_lite::utils::{payload::PacketPayload, random_seed};
use anyhow::Result;
use iota::client as iota_client;
use iota_streams::app::transport::tangle::{client::SendTrytesOptions, PAYLOAD_BYTES};
use iota_streams::app::transport::Transport;
use iota_streams::app_channels::api::tangle::{Address, Author};
use std::string::ToString;

///
/// Channel
///
pub struct Channel {
    author: Author,
    send_opt: SendTrytesOptions,
    channel_address: String,
    announcement_id: String,
    previous_msg_tag: String,
}

impl Channel {
    ///
    /// Initialize the Channel
    ///
    pub fn new(node: String, send_opt: SendTrytesOptions, seed_option: Option<String>) -> Channel {
        let seed = match seed_option {
            Some(seed) => seed,
            None => random_seed::new(),
        };

        let author = Author::new(&seed, "utf-8", PAYLOAD_BYTES, false);
        iota_client::Client::add_node(&node).unwrap();

        let channel_address = author.channel_address().unwrap().to_string();

        Self {
            author: author,
            send_opt: send_opt,
            channel_address: channel_address,
            announcement_id: String::default(),
            previous_msg_tag: String::default(),
        }
    }

    ///
    /// Open a channel
    ///
    pub fn open(&mut self) -> Result<(String, String)> {
        let announcement_message = self.author.announce()?;
        iota_client::Client::get()
            .send_message_with_options(&announcement_message, self.send_opt)?;

        self.announcement_id = announcement_message.link.msgid.to_string();

        Ok((self.channel_address.clone(), self.announcement_id.clone()))
    }

    ///
    /// Write signed packet
    ///
    pub fn write_signed<T>(&mut self, payload: T) -> Result<String>
    where
        T: PacketPayload,
    {
        let signed_packet_link = {
            if self.previous_msg_tag == String::default() {
                let keyload_link =
                    Address::from_str(&self.channel_address, &self.announcement_id).unwrap();
                let msg = self.author.sign_packet(
                    &keyload_link,
                    &payload.public_data(),
                    &payload.masked_data(),
                )?;
                let ret_link = msg.0;
                iota_client::Client::get().send_message_with_options(&ret_link, self.send_opt)?;
                ret_link.link.clone()
            } else {
                let msg = self.author.sign_packet(
                    &Address::from_str(&self.channel_address, &self.previous_msg_tag).unwrap(),
                    &payload.public_data(),
                    &payload.masked_data(),
                )?;
                let ret_link = msg.0;
                iota_client::Client::get().send_message_with_options(&ret_link, self.send_opt)?;
                ret_link.link.clone()
            }
        };

        self.previous_msg_tag = signed_packet_link.msgid.to_string().clone();

        Ok(signed_packet_link.msgid.to_string())
    }
}
