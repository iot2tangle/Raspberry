use crate::api::handlers::{sensor_data_response, status_response};
use crate::iota_channels_lite::channel_author::Channel;
use crate::security::keystore::KeyManager;

use hyper::service::{make_service_fn, service_fn};

use std::sync::{Arc, Mutex};

use hyper::{Body, Method, Request, Response, Server, StatusCode};
type GenericError = Box<dyn std::error::Error + Send + Sync>;
type Result<T> = std::result::Result<T, GenericError>;
static NOTFOUND: &[u8] = b"Not Found";

///
/// Starts the server on the provided port, the server will hand over requests to the handler functions
///
pub async fn start(
    port: u16,
    channel: Arc<Mutex<Channel>>,
    keystore: Arc<Mutex<KeyManager>>,
) -> Result<()> {
    let addr = ([0, 0, 0, 0], port).into();

    let service = make_service_fn(move |_| {
        let channel = channel.clone();
        let keystore = keystore.clone();
        async {
            Ok::<_, GenericError>(service_fn(move |req| {
                responder(req, channel.clone(), keystore.clone())
            }))
        }
    });

    let server = Server::bind(&addr).serve(service);

    println!("Listening on http://{}", addr);

    server.await?;

    Ok(())
}

async fn responder(
    req: Request<Body>,
    channel: Arc<Mutex<Channel>>,
    keystore: Arc<Mutex<KeyManager>>,
) -> Result<Response<Body>> {
    match (req.method(), req.uri().path()) {
        (&Method::POST, "/sensor_data") => sensor_data_response(req, channel, keystore).await,
        (&Method::GET, "/status") => status_response().await,
        _ => Ok(Response::builder()
            .status(StatusCode::NOT_FOUND)
            .body(NOTFOUND.into())
            .unwrap()),
    }
}
