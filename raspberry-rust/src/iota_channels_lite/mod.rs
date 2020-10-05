//!
//! Channels lite
//!
pub mod channel_author;
pub mod channel_subscriber;
pub mod utils;

use iota_streams::app::transport::tangle::client::SendTrytesOptions;

///
/// Network Urls
///
/// Pre-defined iota network urls
///
pub enum Network {
    /// Main network
    ///
    Main,
    /// Dev network
    ///
    Devnet,
    /// Community network
    ///
    Comnet,
    /// Custom network URL
    ///
    /// Arguments:
    ///     * Custome url
    ///     * Min weight magnitude
    ///
    Custom(&'static str, u8),
}

impl Network {
    ///
    /// To string
    ///
    pub fn as_string(&self) -> &'static str {
        match self {
            Self::Custom(url, _) => url,
            Self::Main => "https://nodes.iota.cafe:443",
            Self::Comnet => "https://nodes.comnet.thetangle.org:443",
            Self::Devnet => "https://nodes.devnet.iota.org:443",
        }
    }

    ///
    /// Send Options
    ///
    pub fn send_options(&self) -> SendTrytesOptions {
        let mut send_opt = SendTrytesOptions::default();
        match self {
            Self::Custom(_, mwm) => {
                send_opt.min_weight_magnitude = *mwm;
                send_opt.local_pow = false;
            }
            Self::Main => {
                send_opt.min_weight_magnitude = 14;
                send_opt.local_pow = false;
            }
            Self::Comnet => {
                send_opt.min_weight_magnitude = 10;
                send_opt.local_pow = false;
            }
            Self::Devnet => {
                send_opt.min_weight_magnitude = 9;
                send_opt.local_pow = false;
            }
        }
        send_opt
    }
}
