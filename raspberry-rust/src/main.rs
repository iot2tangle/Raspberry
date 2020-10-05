use local::api::stream_server;
use local::iota_channels_lite::channel_author::Channel;
use local::security::keystore::KeyManager;
use local::types::config::Config;

use std::fs::File;
use std::sync::{Arc, Mutex};

use iota_streams::app::transport::tangle::client::SendTrytesOptions;

#[tokio::main]
async fn main() -> Result<(), Box<dyn std::error::Error + Send + Sync>> {
    //read configuration file
    let config: Config = serde_json::from_reader(File::open("config.json").unwrap()).unwrap();
    let device_name = config.device_name;
    let port = config.port;
    let node = config.node;
    let mwm = config.mwm;
    let local_pow = config.local_pow;

    let store = KeyManager::new(device_name.to_string());

    println!("Starting....");

    let mut send_opt = SendTrytesOptions::default();
    send_opt.min_weight_magnitude = mwm;
    send_opt.local_pow = local_pow;

    let channel = Arc::new(Mutex::new(Channel::new(node, send_opt, None)));
    let (addr, _) = channel.lock().expect("").open().unwrap();
    println!("Channel root: {:?}", addr);
    println!(
        "To Start the Subscriber run: \n
    cargo run --release --example subscriber {:?} \n",
        addr
    );

    let store = Arc::new(Mutex::new(store));

    stream_server::start(port, channel, store).await
}
