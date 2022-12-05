use std::io::{self, Read, Write};
use std::str::FromStr;

use aes::Aes256;
use block_modes::{BlockMode, Cbc};
use block_modes::block_padding::Pkcs7;
use hmac::{Hmac, Mac};
use sha2::Sha256;
use rand::{Rng, thread_rng};

type Aes256Cbc = Cbc<Aes256, Pkcs7>;

const KEY_SIZE: usize = 32;
const IV_SIZE: usize = 16;
const MAC_SIZE: usize = 32;

fn encrypt(key: &[u8], iv: &[u8], data: &[u8]) -> Vec<u8> {
    let cipher = Aes256Cbc::new_var(key, iv).unwrap();
    cipher.encrypt_vec(data)
}

fn decrypt(key: &[u8], iv: &[u8], data: &[u8]) -> Result<Vec<u8>, block_modes::BlockModeError> {
    let cipher = Aes256Cbc::new_var(key, iv).unwrap();
    cipher.decrypt_vec(data)
}

fn compute_mac(key: &[u8], data: &[u8]) -> Vec<u8> {
    let mut hmac = Hmac::<Sha256>::new_varkey(key).unwrap();
    hmac.input(data);
    hmac.result().code().to_vec()
}

fn verify_mac(key: &[u8], data: &[u8], mac: &[u8]) -> bool {
    let mut hmac = Hmac::<Sha256>::new_varkey(key).unwrap();
    hmac.input(data);
    hmac.verify(mac)
}

fn encrypt_message(message: &str) -> (Vec<u8>, Vec<u8>, Vec<u8>) {
    let mut rng = thread_rng();

    let key: Vec<u8> = (0..KEY_SIZE).map(|_| rng.gen()).collect();
    let iv: Vec<u8> = (0..IV_SIZE).map(|_| rng.gen()).collect();

    let message_bytes = message.as_bytes();
    let encrypted_message = encrypt(&key, &iv, &message_bytes);
    let mac = compute_mac(&key, &encrypted_message);

    (key, iv, mac)
}

let (key, iv, mac) = encrypt_message("Mon message secret");
println!("Clé : {:?}", key);
println!("IV : {:?}", iv);
println!("MAC : {:?}", mac);

let decrypted_message = decrypt(&key, &iv, &encrypted_message).unwrap();
println!("Message décrypté : {:?}", decrypted_message);
