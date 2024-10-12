#include <stdio.h>
#include <stdint.h>

int32_t is_ascii(char str[]){
    int byte = 0;
    while ((unsigned char) str[byte] != '\0'){
        if ((unsigned char) str[byte] > 127){
            return 0;
        }
        byte++;
    }
    return 1;
}

int32_t capitalize_ascii(char str[]){
    int32_t byte = 0;
    int char_count = 0;
    while (str[byte] != '\0'){
        if (str[byte] >= 97 && str[byte] <= 122){
            str[byte] -= 32;
            char_count++;
        }
        byte++;
    }
    return char_count;
}

int32_t width_from_start_byte(char start_byte){
    int32_t width = 0;

    int32_t checkWidth = start_byte & 0b11110000;
    
    if (checkWidth == 240){
        width == 4;
    }
    else if (checkWidth == 224){
        width = 3;
    }
    else if (checkWidth == 192){
        width = 2;
    }
    else if (checkWidth == 127){
        width = 1;
    }
    else{
        return -1;
    }

    return width;

    //return checkWidth;
}

int32_t utf8_strlen(char str[]){
    int32_t i = 0;
    int32_t length = 0;
    while (str[i] != '\0'){
        if (width_from_start_byte(str[i]) == 4){
            i += 4;
        }
        else if (width_from_start_byte(str[i]) == 3){
            i += 3;
        }
        else if (width_from_start_byte(str[i]) == 2){
            i += 2;
        }
        else{
            i +=1;
        }
        // else{
        //     length +=0;
        // }
        length++;
    }
    return length;
}

int32_t codepoint_index_to_byte_index(char str[], int32_t cpi){
    int32_t i = 0;
    int32_t current_cpi = 0;

    while (current_cpi != cpi){
        if (width_from_start_byte(str[i]) == 4){
            i += 4;
        }
        else if (width_from_start_byte(str[i]) == 3){
            i += 3;
        }
        else if (width_from_start_byte(str[i]) == 2){
            i += 2;
        }
        else{
            i +=1;
        }

        current_cpi++;
    }

    return i;
}

void utf8_substring(char str[], int32_t cpi_start, int32_t cpi_end, char result[]){
    int32_t i = 0;
    int32_t current_cpi = 0;

    while (str[i] != '\0'){
        if (current_cpi >= cpi_start && current_cpi < cpi_end){
            result[i] = str[i];
        }
        else{
            continue;
        }
        current_cpi++;
    }

    i++;
}

int main(){
    printf("Is 💀 ASCII? %d\n", is_ascii("💀"));
    printf("Is a ASCII? %d\n", is_ascii("a"));

    int32_t ret = 0;
    char str_cap[] = "abcd";
    ret = capitalize_ascii(str_cap);
    printf("Capitalized String: %s\nCharacters updated: %d\n", str_cap, ret);

    char s[] = "Héy"; // same as { 'H', 0xC3, 0xA9, 'y', 0 },   é is start byte + 1 cont. byte
    printf("Width: %d bytes\n", width_from_start_byte(s[1]));
    printf("Width: %d bytes\n", width_from_start_byte(s[2])); // start byte 0xA9 is a continuation byte, not a start byte

    char str[] = "Joséph";
    printf("Length of string %s is %d\n", str, utf8_strlen(str));  // 6 codepoints, (even though 7 bytes)

    //char str[] = "Joséph";
    int32_t idx = 4;
    printf("Codepoint index %d is byte index %d\n", idx, codepoint_index_to_byte_index("Joséph", idx));

    // char result[17];
    // utf8_substring("🦀🦮🦮🦀🦀🦮🦮", 3, 7, result);
    // printf("String: %s\nSubstring: %s", result); // these emoji are 4 bytes long
    
    //char letter[] = "💀";
    //printf("%d", is_ascii(letter));
}