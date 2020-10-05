//!
//! To Generate a new Random Seed
//!
extern crate rand;
use rand::Rng;

///
/// Generates a new random String of 81 Chars of A..Z and 9
///
pub fn new() -> String {
    const CHARSET: &[u8] = b"ABCDEFGHIJKLMNOPQRSTUVWXYZ9";
    const SEED_LEN: usize = 81;
    let mut rng = rand::thread_rng();

    let seed: String = (0..SEED_LEN)
        .map(|_| {
            let idx = rng.gen_range(0, CHARSET.len());
            CHARSET[idx] as char
        })
        .collect();

    seed
}
