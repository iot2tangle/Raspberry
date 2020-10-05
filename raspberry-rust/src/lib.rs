//!
//! Channel Library
//!
#![deny(
    bad_style,
    trivial_casts,
    trivial_numeric_casts,
    unsafe_code,
    unstable_features
)]
#![cfg_attr(not(debug_assertions), deny(warnings))]

pub mod api;
pub mod iota_channels_lite;
pub mod security;
pub mod types;

use crate::security::keystore::calculate_hash;
fn authenticate(key: &str, hash: String) -> bool {
    calculate_hash(key.to_string()) == hash
}

use std::time::{SystemTime, UNIX_EPOCH};
fn timestamp_in_sec() -> u64 {
    SystemTime::now()
        .duration_since(UNIX_EPOCH)
        .unwrap()
        .as_secs()
}
