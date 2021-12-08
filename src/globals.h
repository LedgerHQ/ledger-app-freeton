#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include "os.h"
#include "ux.h"
#include "os_io_seproxyhal.h"
#include "errors.h"
#include "cell.h"

#define P1_CONFIRM 0x01
#define P1_NON_CONFIRM 0x00

#define PUBLIC_KEY_LENGTH 32
#define ADDRESS_LENGTH 32
#define PUBKEY_STR_SIZE 67
#define ADDRESS_STR_SIZE 67
#define AMOUNT_STR_SIZE 27
#define BIP32_PATH 5
#define TO_SIGN_LENGTH 32
#define SIGNATURE_LENGTH 64
#define MAX_AMOUNT_LENGTH 16
#define HASH_SIZE 32
#define BOC_GENERIC_TAG 0xb5ee9c72
#define MAX_ROOTS_COUNT 1
#define INPUT_ID 0x315ef935

extern ux_state_t ux;
// display stepped screens
extern unsigned int ux_step;
extern unsigned int ux_step_count;

#define MAX_CONTRACT_CELLS_COUNT 6
#define MAX_MESSAGE_CELLS_COUNT 2
#define HASHES_BUFFER_SIZE (MAX_CONTRACT_CELLS_COUNT * HASH_SIZE)
#define MAX_PUBLIC_KEY_CELL_DATA_SIZE 36 // label(3) + public key(32) + tag(1)

void reset_app_context(void);

typedef struct BocContext_t {
    Cell_t cells[MAX_CONTRACT_CELLS_COUNT];
    uint8_t hashes[HASHES_BUFFER_SIZE];
    uint8_t cell_depth[MAX_CONTRACT_CELLS_COUNT];
    uint8_t public_key_cell_data[MAX_PUBLIC_KEY_CELL_DATA_SIZE];
    uint8_t cells_count;
    uint8_t public_key_cell_index;
    uint8_t public_key_label_size_bits;
} BocContext_t;

typedef struct AddressContext_t {
    uint8_t address[ADDRESS_LENGTH];
    char address_str[ADDRESS_STR_SIZE];
} AddressContext_t;

typedef struct PublicKeyContext_t {
    uint8_t public_key[PUBLIC_KEY_LENGTH];
    char public_key_str[PUBKEY_STR_SIZE];
} PublicKeyContext_t;

typedef struct SignContext_t {
    uint32_t account_number;
    uint64_t amount;
    uint8_t  dst_account_id[ADDRESS_LENGTH];
    uint8_t  to_sign[TO_SIGN_LENGTH];
    uint8_t  signature[SIGNATURE_LENGTH];
    char     dst_address_str[ADDRESS_LENGTH];
    char     amount_str[AMOUNT_STR_SIZE];
} SignContext_t;

typedef union {
    PublicKeyContext_t pk_context;
    AddressContext_t addr_context;
    SignContext_t sign_context;
} DataContext_t;

typedef struct ContractContext_t {
    uint8_t const* code_hash;
    uint8_t const* wallet;
    uint8_t wallet_size;
    uint8_t wallet_cells_count;
    uint8_t wallet_code_child_depth;
    uint8_t wallet_data_child_depth;
} ContractContext_t;

extern BocContext_t boc_context;
extern DataContext_t data_context;

extern ContractContext_t contract_context;

#endif
