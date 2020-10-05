use crate::authenticate;
use crate::security::keystore::{calculate_hash, KeyManager};
use crate::timestamp_in_sec;
use crate::types::sensor_data::SensorData;
use std::sync::{Arc, Mutex};

use crate::iota_channels_lite::channel_author::Channel;
use crate::iota_channels_lite::utils::payload::json::PayloadBuilder;

type GenericError = Box<dyn std::error::Error + Send + Sync>;
type Result<T> = std::result::Result<T, GenericError>;

use hyper::{header, Body, Request, Response, StatusCode};

///
/// Handles the status request returning status code 200 if the server is online
///
pub async fn status_response() -> Result<Response<Body>> {
    Ok(Response::builder().status(200).body(Body::from("OK"))?)
}

///
/// Handles the reuqest from the sensor by parsing the provieded data into the SensorData Format.
/// It authenticates the device through the "device" attribute, and if successfull published the data to the Tangle
/// through the streams channel
///
pub async fn sensor_data_response(
    req: Request<Body>,
    channel: Arc<Mutex<Channel>>,
    keystore: Arc<Mutex<KeyManager>>,
) -> Result<Response<Body>> {
    let data = hyper::body::to_bytes(req.into_body()).await?;

    let response;

    let json_data: serde_json::Result<SensorData> = serde_json::from_slice(&data);
    match json_data {
        Ok(mut sensor_data) => {
            let hash = keystore
                .lock()
                .expect("lock keystore")
                .keystore
                .api_key_author
                .clone();
            if authenticate(&sensor_data.device, hash.clone()) {
                sensor_data.device.to_string().push_str("_id");
                sensor_data.device = calculate_hash(sensor_data.device);
                sensor_data.timestamp = serde_json::Value::from(timestamp_in_sec());
                println!(
                    "POST /sensor_data -- {:?} -- authorized request by device",
                    timestamp_in_sec()
                );
                let mut channel = channel.lock().unwrap();
                match channel
                    .write_signed(PayloadBuilder::new().public(&sensor_data).unwrap().build())
                {
                    Ok(_) => {
                        response = Response::builder()
                            .status(StatusCode::OK)
                            .header(header::CONTENT_TYPE, "application/json")
                            .body(Body::from("Data Sent sucessfully To Tangle"))?;
                    }
                    Err(_e) => {
                        println!(
                            "POST /sensor_data Error: Malformed json, use xdk2streams json format"
                        );
                        response = Response::builder()
                            .status(500)
                            .header(header::CONTENT_TYPE, "application/json")
                            .body(Body::from("Error while sending data"))?;
                    }
                };
            } else {
                response = Response::builder()
                    .status(StatusCode::UNAUTHORIZED)
                    .header(header::CONTENT_TYPE, "application/json")
                    .body(Body::from("Unauthorized"))?;
                println!(
                    "POST /sensor_data -- {:?} -- unauthorized request blocked",
                    timestamp_in_sec()
                );
            }
        }
        Err(_e) => {
            response = Response::builder()
                .status(500)
                .header(header::CONTENT_TYPE, "application/json")
                .body(Body::from("Error while parsing input data"))?;
        }
    }
    Ok(response)
}
