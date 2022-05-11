#include <stdio.h>
#include <string.h>
#include <stdlib.h>

u_int8_t *in = "\xA6\xF0\xF7\xFA\xAD\x76\xBF\xD5\x20\xF7\x9B\x96\x06\x85\x40\x20\x10\x34\x3F\xA7\x9F\x40\xEE\x32\xC8\x0E\xA2\x97\xDB\x79\x96\xFB\x0D\xCA\x83\xDA\x65\x77\x3E\x0C\x9A\x97\xCF\x6F\xB2\x3B\x1F\x06\xC5\x5A\x75\x35\x48\x1E\xD6\x83\xC4\x75\x76\x18\xD4\x0E\xD3\xCB\xED\x30\x3D\xBD\x0E\xB7\xF4\xE8\xF2\x9C\x7E\x62\xD9\xDB\xE5\x39\xBD\x0C\x9A\x83\xD2\x6E\xF3\x5B\xDE\x0E\xD3\xD3\xEB\xB7\x1A\x94\x26\x97\xE9\xA0\x75\x78\x0D\x7A\xCF\xDD\x6F\xBB\xFB\xAD\x06\xC1\xE5\x65\x72\xBB\x4C\x77\x39\xCB\x20\xF8\xDB\x5E\xD6\xB3\xDF\x2E\x97\x6B\x19\x5E\x83\xF2\x20\x7A\x59\x9C\x0F\x83\xE8\x6F\x10\xB9\xCC\x0E\xFF\x50\xEE\x32\x68\x4E\x4B\xD3\xC3\xF9\x30\x68\x1E\x6E\x83\xF4\xEE\x70\xF9\x7E\x02\xD1\xCA\xE7\x77\x0A";

u_int8_t *out;

// hdr_octets = 172 + 1 = 173
// hdr_septets = (173 * 8 + 6) / 7 = 198
// fill_bits = (198 * 7) % 8 = 2
// user_data_bits = > 8 ? 2048?
// header_size = udhi ? 1 : 0;
// enc_text_bits = user_data_bits - (hdr_septets * 7) = 662
// text_septets = enc_text_bits / 7

void
DL_UTIL_7BIT_CHAR_PACKING_unpack_from_offset(u_int8_t *packed_buffer,
											 u_int8_t *unpacked_buffer,
											 u_int16_t num_chars,
											 u_int8_t fill_bits)
{
	u_int8_t bit_position;  /* this variable points to the bit position (0-7) */
	/* where the lsb of the next septet is located    */
	u_int16_t i;  /* index into unpacked_buffer */
	u_int16_t j;  /* index into packed_buffer   */
	u_int8_t next_char;

	/* assert (fill_bits <= 7); */

	for (i = 0, j = 0, bit_position = fill_bits; i < num_chars; i++)
	{
		switch (bit_position)
		{
			case 0:
				next_char = packed_buffer[j];
				bit_position = 7;
				break;
			case 1:
				next_char = packed_buffer[j] >> bit_position;
				bit_position--;
				j++;
				break;
			default:  /* 2 through 7 */
				next_char = packed_buffer[j] >> bit_position;
				next_char |= packed_buffer[j+1] << (8 - bit_position);
				bit_position--;
				j++;
				break;
		}

		unpacked_buffer[i] = next_char & 0x7F;
	}
}

int main(void) {
	out = malloc(200);
	printf("%d %d\n", strlen(in), strlen(out));
	DL_UTIL_7BIT_CHAR_PACKING_unpack_from_offset(in, out, 210, 1);
	printf("%d %d\n", strlen(in), strlen(out));

	FILE * pFile=fopen("hex_c", "wb");
	if (pFile!=NULL) {
		fwrite (in , sizeof(u_int8_t), strlen(in), pFile);
		fclose (pFile);
	}

	printf("%s\n", out);

	free(out);
	return 0;
}
