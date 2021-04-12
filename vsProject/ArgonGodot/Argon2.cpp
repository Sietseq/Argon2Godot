#include "Argon2.h"
#include <argon2.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <sstream>
#include <iomanip>


#define HASHLEN 32
#define SALTLEN 16

using namespace godot;

void Argon2::_register_methods()
{
	register_method("RawHash", &Argon2::RawHash);
}

void Argon2::_init()
{
	// Initialize variables
}

Argon2::Argon2()
{
	// Set up
}

Argon2::~Argon2()
{
	// Clean up
}

String Argon2::RawHash(String str, String slt)
{
    std::string string = str.alloc_c_string(); // Godot string to c string
    const char* cstr = string.c_str(); // c string to a const char array

    uint8_t* pwd = (uint8_t*)_strdup(cstr); // const char array to uint8_t array
    uint32_t pwdlen = strlen((char*)pwd); // Length of the password

    uint8_t hash1[HASHLEN];

    // Create salt
    uint8_t salt[SALTLEN];
    memset(salt, 0x00, SALTLEN);

    std::string slt_str = slt.alloc_c_string(); // Make input string into a cstring

    // Loops through the string and sets each index of salt to the char of the slt_string
    if (slt_str.length() == SALTLEN)
    {
        try
        {
            for (int i = 0; i < SALTLEN; i++)
            {
                salt[i] = slt_str[i] - '0';
            }
        }
        catch (std::invalid_argument const& e)
        {
            std::cout << "Bad input: std::invalid_argument thrown" << '\n';
        }
        catch (std::out_of_range const& e)
        {
            std::cout << "Integer overflow: std::out_of_range thrown" << '\n';
        }
    }
    else
    {
        std::cout << "Salt length is not correct" << std::endl;
    }


    uint32_t t_cost = 2;            // 2-pass computation
    uint32_t m_cost = (1 << 16);      // 64 mebibytes memory usage
    uint32_t parallelism = 1;       // number of threads and lanes

    // low-level API
    argon2_context context = {
        hash1,  /* output array, at least HASHLEN in size */
        HASHLEN, /* digest length */
        pwd, /* password array */
        pwdlen, /* password length */
        salt,  /* salt array */
        SALTLEN, /* salt length */
        NULL, 0, /* optional secret data */
        NULL, 0, /* optional associated data */
        t_cost, m_cost, parallelism, parallelism,
        ARGON2_VERSION_13, /* algorithm version */
        NULL, NULL, /* custom memory allocation / deallocation functions */
        /* by default only internal memory is cleared (pwd is not wiped) */
        ARGON2_DEFAULT_FLAGS
    };

    int rc = argon2id_ctx(&context);
    if (ARGON2_OK != rc)
    {
        printf("Error: %s\n", argon2_error_message(rc));
        exit(1);
    }

    static constexpr char hex[] = "0123456789abcdef";  // Hex values
    String result("0000000000000000000000000000000000000000000000000000000000000000");   // Result string

    // Loops through the hash and turns it into a godot string
    int x = 0;
    for (int i = 0; i < HASHLEN; ++i)
    {
        result[x] = hex[hash1[i] / 16];
        x++;
        result[x] = hex[hash1[i] % 16];
        x++;
    }

    return result;
}