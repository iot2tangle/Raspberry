use serde_derive::Deserialize;
use serde_derive::Serialize;
use serde_json::Value;

#[derive(Serialize, Deserialize, Debug)]
pub struct SensorType {
    pub sensor: String,
    pub data: Vec<Value>,
}
