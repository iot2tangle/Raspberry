//!
//! Payload Module
//!
use base64::{decode_config, encode_config, URL_SAFE_NO_PAD};
use iota_conversion::trytes_converter::{to_string as trytes_to_string, to_trytes};
use iota_streams::ddml::types::Bytes;
use serde::{de::DeserializeOwned, Serialize};
use std::marker::PhantomData;

///
/// Simple Trait to transform the payload to string using any serde serializer
///
pub trait PayloadSerializer {
    ///
    /// Transform data to String
    ///
    fn serialize_data<T: Serialize>(data: &T) -> failure::Fallible<String>;

    ///
    /// Transform data to String
    ///
    fn deserialize_data<T: DeserializeOwned>(data: &[u8]) -> failure::Fallible<T>;
}

///
/// Payload
///
pub trait PacketPayload {
    ///
    /// Return the public payload data
    ///
    fn public_data(&self) -> &Bytes;
    ///
    /// Return the masked payload data
    ///
    fn masked_data(&self) -> &Bytes;
}

///
/// Packet
///
pub struct Payload<S> {
    public: Bytes,
    masked: Bytes,
    _marker: PhantomData<S>,
}

impl<S> Payload<S>
where
    S: PayloadSerializer,
{
    ///
    /// Unwrap JSON Data
    ///
    pub fn unwrap_data(data: &str) -> failure::Fallible<Option<String>> {
        let data_str = data.to_string();
        if data_str.len() == 0 {
            return Ok(None);
        }
        let raw = trytes_to_string(&data.to_string())?;
        let decode_data = decode_config(&raw, URL_SAFE_NO_PAD)?;
        Ok(Some(String::from_utf8(decode_data).unwrap()))
    }
}

impl<S> PacketPayload for Payload<S> {
    fn public_data(&self) -> &Bytes {
        &self.public
    }
    fn masked_data(&self) -> &Bytes {
        &self.masked
    }
}

///
/// Payload Builder
///
pub struct PayloadBuilder<S> {
    p_data: String,
    m_data: String,
    _marker: PhantomData<S>,
}

impl<S> PayloadBuilder<S>
where
    S: PayloadSerializer,
{
    ///
    /// Create Instance
    ///
    pub fn new() -> Self {
        PayloadBuilder {
            p_data: String::new(),
            m_data: String::new(),
            _marker: PhantomData,
        }
    }

    ///
    /// Public Data
    ///
    pub fn public<T>(&mut self, data: &T) -> failure::Fallible<&mut Self>
    where
        T: Serialize,
    {
        // let json_payload = serde_json::to_string(data).unwrap();
        let payload_str = S::serialize_data(data)?;
        self.p_data = to_trytes(&encode_config(&payload_str, URL_SAFE_NO_PAD))?;
        Ok(self)
    }

    ///
    /// Public Data
    ///
    pub fn masked<T>(&mut self, data: &T) -> failure::Fallible<&mut Self>
    where
        T: Serialize,
    {
        // let json_payload = serde_json::to_string(data).unwrap();
        let payload_str = S::serialize_data(data)?;
        self.m_data = to_trytes(&encode_config(&payload_str, URL_SAFE_NO_PAD))?;
        Ok(self)
    }

    ///
    /// Build
    ///
    pub fn build(&self) -> Payload<S> {
        Payload {
            public: Bytes(self.p_data.as_bytes().to_vec()),
            masked: Bytes(self.m_data.as_bytes().to_vec()),
            _marker: PhantomData,
        }
    }
}

pub mod json {
    //!
    //! JSON Payload Serialization module
    //!
    use super::PayloadSerializer;
    use serde::{de::DeserializeOwned, Serialize};

    ///
    /// Implementation of JSON Serialize
    ///
    pub struct JsonSerializer;

    impl PayloadSerializer for JsonSerializer {
        fn serialize_data<T: Serialize>(data: &T) -> failure::Fallible<String> {
            serde_json::to_string(data).map_err(|e| failure::format_err!("{:#?}", e))
        }

        fn deserialize_data<T: DeserializeOwned>(data: &[u8]) -> failure::Fallible<T> {
            serde_json::from_slice(data).map_err(|e| failure::format_err!("{:#?}", e))
        }
    }

    /// Payload JSON
    ///
    pub type Payload = super::Payload<JsonSerializer>;

    /// Payload Builder in Json Format
    ///
    pub type PayloadBuilder = super::PayloadBuilder<JsonSerializer>;
}
