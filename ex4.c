//課題4用プログラム

#include<stdio.h>
void sb(unsigned char[4][4]);
void sr(unsigned char[4][4]);
void mc(unsigned char[4][4]);
unsigned char gmul(unsigned char a, unsigned char b);
void ark(unsigned char[4][4]);
void ke();
void printMatrix(char*, unsigned char[4][4]);
void stringToMatrix(const unsigned char[], unsigned char[4][4]);
void midEncrypt(unsigned char[4][4]);
int deffByteBetween(const unsigned char[4][4], const unsigned char[4][4]);
void printPosOfDiff(const unsigned char[4][4], const unsigned char[4][4]);
void initKey(void);
int generateKey(void);
// void inv_sb();
// void inv_sr();
// void inv_mc();


//平文ペア
unsigned char pt[13][2][33] =
	{{"0250f4a5f85384cf4917b7a1e298c667",
		"0244f4a5f853f6cf4917b7b05598c667"},

	 {"28eb084c66ef3e247caf3ab4f207a845",
	 	"28eb08b1a5ef3e247cde3ab4f2074945"},

	 {"e8841c873ba019aa6211fde4d71d9861",
	  "e8848b873ba019c63011fde4d78a9861"},

	 {"c4652154f6b9ff7de4281d6841ced479",
	 	"c4651b54f6b9ff9c9c281d68418cd479"},

	 {"a40eebb0341c93da46a169fdfe8946fd",
	 	"a40eeb4f221c93da463269fdfe89e2fd"},

	 {"1b562cadb3a05af7ddb5f29dd7628312",
	 	"40562cadb3a55af7ddb5a69dd7628398"},

	 {"c51ca80eb0c57f24d78d8f9d7f87af9a",
	 	"c51c470eb0c57f14ca8d8f9d7f7baf9a"},

	 {"aef69ab48f192d88c9f8ac5958bd098c",
	 	"ae319ab48f194a88c9f8ac9defbd098c"},

	 {"a4270bdf06f1df3ebc16ed71679efc12",
	  "a4270b3512f1df3ebc11ed71679ede12"},

	 {"050656bf6e39045b25d01828df40bd8d",
	  "280656bf6ee7045b25d04228df40bd30"},

	 {"25940e5ee617799369d5b79ccbf5f5ac",
	 	"25b40e5ee6178e9369d5b7d372f5f5ac"},

	 {"568ebe3af27f97d3badc39e2c34d370b",
	 	"568eaf3af27f970d38dc39e2c30d370b"},

	 {"92d412ac62f1ed57172f75536f95297f",
	 	"12d412ac6235ed57172f1c536f95292b"}};

//13の平文ペアを格納するための配列
unsigned char state[13][2][4][4];





unsigned char state1[4][4] =
	{{0x00,0x00,0x00,0x00},
	 {0x00,0x00,0x00,0x00},
	 {0x00,0x00,0x00,0x00},
	 {0x00,0x00,0x00,0x00}};

unsigned char state2[4][4] =
 	{{0x01,0x00,0x00,0x00},
 	 {0x00,0x00,0x00,0x00},
 	 {0x00,0x00,0x00,0x00},
 	 {0x00,0x00,0x00,0x00}};

unsigned char key[4][4];
unsigned char nextKey[4][4] = {0};

// unsigned char
// key11,key12,key13,key14,key21,key22,key23,key24,
// key31,key32,key33,key34,key41,key42,key43,key44;
unsigned char w[176];


void printMatrix(char *explanation, unsigned char mat[4][4]){
	printf("%s : 0x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x\n"
		, explanation,
			mat[0][0],mat[1][0],mat[2][0],mat[3][0],
			mat[0][1],mat[1][1],mat[2][1],mat[3][1],
			mat[0][2],mat[1][2],mat[2][2],mat[3][2],
			mat[0][3],mat[1][3],mat[2][3],mat[3][3]);
}

//32桁の半角文字列（平文や鍵）を行列に格納 するための関数．
void stringToMatrix(const unsigned char str[], unsigned char mat[4][4]){
  int i;
  unsigned char temp[3];
  temp[2] = '\0';
  for(i = 0; i < 16; i++){
    temp[0] = str[i * 2];
    temp[1] = str[i * 2 + 1];
    mat[i % 4][i / 4] = (unsigned char)strtol(&temp, NULL, 16);
  }
}

int deffByteBetween(const unsigned char mt1[4][4], const unsigned char mt2[4][4]){
	int num = 0;
	int i, j;
	for(i = 0; i < 4; i++){
		for(j = 0; j < 4; j++){
			if(mt1[i][j] != mt2[i][j]) num++;
		}
	}
	return num;
}

void printPosOfDiff(const unsigned char mt1[4][4], const unsigned char mt2[4][4]){
	int num = deffByteBetween(mt1, mt2);
	int result[16][2];
	int a = 0;
	int i, j;

	for(i = 0; i < 4; i++){
		for(j = 0; j < 4; j++){
			if(mt1[i][j] != mt2[i][j]){
				result[a][0] = i;
				result[a][1] = j;
				a++;
			}
		}
	}

	for(i = 0; i < num; i++){
		printf("[%d][%d] ", result[i][0], result[i][1]);
	}
	printf("\n");

}

int main(void){


	int i, j;


	for(i = 0; i < 13; i++){
		for(j = 0; j < 2; j++){
			stringToMatrix(pt[i][j], state[i][j]);
		}
	}


	for(i = 0; i < 13; i++){
		initKey();
		printf("平文ペア%d\n", i + 1);

		printMatrix("平文1　", state[i][0]);
		printMatrix("平文2　", state[i][1]);
		// printf("差分　　: %dバイト\n", deffByteBetween(state[i][0], state[i][1]));
		// printf("差分位置: ");
		// printPosOfDiff(state[i][0], state[i][0]);

		while(generateKey() && (deffByteBetween(state[i][0], state[i][1]) > 1)){
			midEncrypt(state[i][0]);
			midEncrypt(state[i][1]);
		}
		printMatrix("中間値1", state[i][0]);
		printMatrix("中間値2", state[i][1]);
		printf("差分　　: %dバイト\n", deffByteBetween(state[i][0], state[i][1]));
		printMatrix("鍵　　　", key);
		// printf("差分位置: ");
		// printPosOfDiff(state[i][0], state[i][0]);

		putchar('\n');
	}

	return 0;
}

int generateKey(void){
	int i, j;
	for(i = 0; i < 4;i ++){
		for(j = 0; j < 4; j++){
			key[i][j] = nextKey[i][j];
		}
	}

	// printMatrix("鍵", key);


	if(nextKey[3][3] < 255){
		nextKey[3][3]++;
	}else{
		nextKey[3][3] = 0;
		if(nextKey[2][2] < 255){
			nextKey[2][2]++;
		}else{
			nextKey[2][2] = 0;
			if(nextKey[1][1] < 255){
				nextKey[1][1]++;
			}else{
				nextKey[1][1] = 0;
				if(nextKey[0][0] < 255){
					nextKey[0][0]++;
				}else{
					return 0; //これ以上鍵を生成できない．
				}
			}
		}
	}
	return 1;
}

void initKey(void){
	int i, j;
	for(i = 0; i < 4; i++){
		for(j = 0; j < 4; j++){
			nextKey[i][j] = 0;
		}
	}
}

void midEncrypt(unsigned char st[4][4]){

	int i, j;
	// for(i = 0; i < 4; i++){
	// 	for(j = 0; j < 4; j++){
	// 		key[j][i] = 4 * i + j;
	// 	}
	// }

	ke();
	ark(st);


	for(i = 1; i <= 1/* 元々は 10 */; i++){
		key[0][0] = w[16 * i];
		key[1][0] = w[16 * i +  1];
		key[2][0] = w[16 * i +  2];
		key[3][0] = w[16 * i +  3];
		key[0][1] = w[16 * i +  4];
		key[1][1] = w[16 * i +  5];
		key[2][1] = w[16 * i +  6];
		key[3][1] = w[16 * i +  7];
		key[0][2] = w[16 * i +  8];
		key[1][2] = w[16 * i +  9];
		key[2][2] = w[16 * i + 10];
		key[3][2] = w[16 * i + 11];
		key[0][3] = w[16 * i + 12];
		key[1][3] = w[16 * i + 13];
		key[2][3] = w[16 * i + 14];
		key[3][3] = w[16 * i + 15];

		sb(st);
		sr(st);
		/*if(i != 10)*/	mc(st);
		// ark();
	}
}


void sb(unsigned char st[4][4]){
	unsigned char sbox[256] =
	 {0x63,0x7c,0x77,0x7b,0xf2,0x6b,0x6f,0xc5,0x30,0x01,0x67,0x2b,0xfe,0xd7,0xab,0x76,
		0xca,0x82,0xc9,0x7d,0xfa,0x59,0x47,0xf0,0xad,0xd4,0xa2,0xaf,0x9c,0xa4,0x72,0xc0,
		0xb7,0xfd,0x93,0x26,0x36,0x3f,0xf7,0xcc,0x34,0xa5,0xe5,0xf1,0x71,0xd8,0x31,0x15,
		0x04,0xc7,0x23,0xc3,0x18,0x96,0x05,0x9a,0x07,0x12,0x80,0xe2,0xeb,0x27,0xb2,0x75,
		0x09,0x83,0x2c,0x1a,0x1b,0x6e,0x5a,0xa0,0x52,0x3b,0xd6,0xb3,0x29,0xe3,0x2f,0x84,
		0x53,0xd1,0x00,0xed,0x20,0xfc,0xb1,0x5b,0x6a,0xcb,0xbe,0x39,0x4a,0x4c,0x58,0xcf,
		0xd0,0xef,0xaa,0xfb,0x43,0x4d,0x33,0x85,0x45,0xf9,0x02,0x7f,0x50,0x3c,0x9f,0xa8,
		0x51,0xa3,0x40,0x8f,0x92,0x9d,0x38,0xf5,0xbc,0xb6,0xda,0x21,0x10,0xff,0xf3,0xd2,
		0xcd,0x0c,0x13,0xec,0x5f,0x97,0x44,0x17,0xc4,0xa7,0x7e,0x3d,0x64,0x5d,0x19,0x73,
		0x60,0x81,0x4f,0xdc,0x22,0x2a,0x90,0x88,0x46,0xee,0xb8,0x14,0xde,0x5e,0x0b,0xdb,
		0xe0,0x32,0x3a,0x0a,0x49,0x06,0x24,0x5c,0xc2,0xd3,0xac,0x62,0x91,0x95,0xe4,0x79,
		0xe7,0xc8,0x37,0x6d,0x8d,0xd5,0x4e,0xa9,0x6c,0x56,0xf4,0xea,0x65,0x7a,0xae,0x08,
		0xba,0x78,0x25,0x2e,0x1c,0xa6,0xb4,0xc6,0xe8,0xdd,0x74,0x1f,0x4b,0xbd,0x8b,0x8a,
		0x70,0x3e,0xb5,0x66,0x48,0x03,0xf6,0x0e,0x61,0x35,0x57,0xb9,0x86,0xc1,0x1d,0x9e,
		0xe1,0xf8,0x98,0x11,0x69,0xd9,0x8e,0x94,0x9b,0x1e,0x87,0xe9,0xce,0x55,0x28,0xdf,
		0x8c,0xa1,0x89,0x0d,0xbf,0xe6,0x42,0x68,0x41,0x99,0x2d,0x0f,0xb0,0x54,0xbb,0x16};

	st[0][0] = sbox[st[0][0]];
	st[0][1] = sbox[st[0][1]];
	st[0][2] = sbox[st[0][2]];
	st[0][3] = sbox[st[0][3]];
	st[1][0] = sbox[st[1][0]];
	st[1][1] = sbox[st[1][1]];
	st[1][2] = sbox[st[1][2]];
	st[1][3] = sbox[st[1][3]];
	st[2][0] = sbox[st[2][0]];
	st[2][1] = sbox[st[2][1]];
	st[2][2] = sbox[st[2][2]];
	st[2][3] = sbox[st[2][3]];
	st[3][0] = sbox[st[3][0]];
	st[3][1] = sbox[st[3][1]];
	st[3][2] = sbox[st[3][2]];
	st[3][3] = sbox[st[3][3]];
}

void sr(unsigned char st[4][4]){
	unsigned char tmp;

	//意味がないからコメントアウト
	// st[0][0] = st[0][0];
	// st[0][1] = st[0][1];
	// st[0][2] = st[0][2];
	// st[0][3] = st[0][3];

	tmp      = st[1][0];
	st[1][0] = st[1][1];
	st[1][1] = st[1][2];
	st[1][2] = st[1][3];
	st[1][3] = tmp;
		tmp      = st[2][0];
	st[2][0] = st[2][2];
	st[2][2] = tmp;
	tmp      = st[2][1];
	st[2][1] = st[2][3];
	st[2][3] = tmp;
	tmp      = st[3][0];
	st[3][0] = st[3][3];
	st[3][3] = st[3][2];
	st[3][2] = st[3][1];
	st[3][1] = tmp;
}

void mc(unsigned char st[4][4]) {
	unsigned char tmp[4][4];

	tmp[0][0]=gmul(st[0][0],2)^gmul(st[1][0],3)^gmul(st[2][0],1)^gmul(st[3][0],1);
	tmp[1][0]=gmul(st[0][0],1)^gmul(st[1][0],2)^gmul(st[2][0],3)^gmul(st[3][0],1);
	tmp[2][0]=gmul(st[0][0],1)^gmul(st[1][0],1)^gmul(st[2][0],2)^gmul(st[3][0],3);
	tmp[3][0]=gmul(st[0][0],3)^gmul(st[1][0],1)^gmul(st[2][0],1)^gmul(st[3][0],2);
	tmp[0][1]=gmul(st[0][1],2)^gmul(st[1][1],3)^gmul(st[2][1],1)^gmul(st[3][1],1);
	tmp[1][1]=gmul(st[0][1],1)^gmul(st[1][1],2)^gmul(st[2][1],3)^gmul(st[3][1],1);
	tmp[2][1]=gmul(st[0][1],1)^gmul(st[1][1],1)^gmul(st[2][1],2)^gmul(st[3][1],3);
	tmp[3][1]=gmul(st[0][1],3)^gmul(st[1][1],1)^gmul(st[2][1],1)^gmul(st[3][1],2);
	tmp[0][2]=gmul(st[0][2],2)^gmul(st[1][2],3)^gmul(st[2][2],1)^gmul(st[3][2],1);
	tmp[1][2]=gmul(st[0][2],1)^gmul(st[1][2],2)^gmul(st[2][2],3)^gmul(st[3][2],1);
	tmp[2][2]=gmul(st[0][2],1)^gmul(st[1][2],1)^gmul(st[2][2],2)^gmul(st[3][2],3);
	tmp[3][2]=gmul(st[0][2],3)^gmul(st[1][2],1)^gmul(st[2][2],1)^gmul(st[3][2],2);
	tmp[0][3]=gmul(st[0][3],2)^gmul(st[1][3],3)^gmul(st[2][3],1)^gmul(st[3][3],1);
	tmp[1][3]=gmul(st[0][3],1)^gmul(st[1][3],2)^gmul(st[2][3],3)^gmul(st[3][3],1);
	tmp[2][3]=gmul(st[0][3],1)^gmul(st[1][3],1)^gmul(st[2][3],2)^gmul(st[3][3],3);
	tmp[3][3]=gmul(st[0][3],3)^gmul(st[1][3],1)^gmul(st[2][3],1)^gmul(st[3][3],2);

	st[0][0]=tmp[0][0];
	st[0][1]=tmp[0][1];
	st[0][2]=tmp[0][2];
	st[0][3]=tmp[0][3];
	st[1][0]=tmp[1][0];
	st[1][1]=tmp[1][1];
	st[1][2]=tmp[1][2];
	st[1][3]=tmp[1][3];
	st[2][0]=tmp[2][0];
	st[2][1]=tmp[2][1];
	st[2][2]=tmp[2][2];
	st[2][3]=tmp[2][3];
	st[3][0]=tmp[3][0];
	st[3][1]=tmp[3][1];
	st[3][2]=tmp[3][2];
	st[3][3]=tmp[3][3];
}

//gmul
unsigned char gmul(unsigned char a, unsigned char b) {
	unsigned char p = 0;
	unsigned char counter;
	unsigned char hi_bit_set;
	for(counter = 0; counter < 8; counter++) {
		if((b & 1) == 1)
			p ^= a;
		hi_bit_set = (a & 0x80);
		a <<= 1;
		if(hi_bit_set == 0x80)
			a ^= 0x1b;
		b >>= 1;
	}
	return p;
}

void ark(unsigned char st[4][4]) {
	st[0][0] = st[0][0] ^ key[0][0];
	st[0][1] = st[0][1] ^ key[0][1];
	st[0][2] = st[0][2] ^ key[0][2];
	st[0][3] = st[0][3] ^ key[0][3];
	st[1][0] = st[1][0] ^ key[1][0];
	st[1][1] = st[1][1] ^ key[1][1];
	st[1][2] = st[1][2] ^ key[1][2];
	st[1][3] = st[1][3] ^ key[1][3];
	st[2][0] = st[2][0] ^ key[2][0];
	st[2][1] = st[2][1] ^ key[2][1];
	st[2][2] = st[2][2] ^ key[2][2];
	st[2][3] = st[2][3] ^ key[2][3];
	st[3][0] = st[3][0] ^ key[3][0];
	st[3][1] = st[3][1] ^ key[3][1];
	st[3][2] = st[3][2] ^ key[3][2];
	st[3][3] = st[3][3] ^ key[3][3];
}

void ke(){
  unsigned char Rcon[16]=
	{0x01,0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0x1b,0x36,0x6c,0xd8,0xab,0x4d,0x9a};
	unsigned char sbox[256] =
	{ 0x63,0x7c,0x77,0x7b,0xf2,0x6b,0x6f,0xc5,0x30,0x01,0x67,0x2b,0xfe,0xd7,0xab,0x76,
		0xca,0x82,0xc9,0x7d,0xfa,0x59,0x47,0xf0,0xad,0xd4,0xa2,0xaf,0x9c,0xa4,0x72,0xc0,
		0xb7,0xfd,0x93,0x26,0x36,0x3f,0xf7,0xcc,0x34,0xa5,0xe5,0xf1,0x71,0xd8,0x31,0x15,
		0x04,0xc7,0x23,0xc3,0x18,0x96,0x05,0x9a,0x07,0x12,0x80,0xe2,0xeb,0x27,0xb2,0x75,
		0x09,0x83,0x2c,0x1a,0x1b,0x6e,0x5a,0xa0,0x52,0x3b,0xd6,0xb3,0x29,0xe3,0x2f,0x84,
		0x53,0xd1,0x00,0xed,0x20,0xfc,0xb1,0x5b,0x6a,0xcb,0xbe,0x39,0x4a,0x4c,0x58,0xcf,
		0xd0,0xef,0xaa,0xfb,0x43,0x4d,0x33,0x85,0x45,0xf9,0x02,0x7f,0x50,0x3c,0x9f,0xa8,
		0x51,0xa3,0x40,0x8f,0x92,0x9d,0x38,0xf5,0xbc,0xb6,0xda,0x21,0x10,0xff,0xf3,0xd2,
		0xcd,0x0c,0x13,0xec,0x5f,0x97,0x44,0x17,0xc4,0xa7,0x7e,0x3d,0x64,0x5d,0x19,0x73,
		0x60,0x81,0x4f,0xdc,0x22,0x2a,0x90,0x88,0x46,0xee,0xb8,0x14,0xde,0x5e,0x0b,0xdb,
		0xe0,0x32,0x3a,0x0a,0x49,0x06,0x24,0x5c,0xc2,0xd3,0xac,0x62,0x91,0x95,0xe4,0x79,
		0xe7,0xc8,0x37,0x6d,0x8d,0xd5,0x4e,0xa9,0x6c,0x56,0xf4,0xea,0x65,0x7a,0xae,0x08,
		0xba,0x78,0x25,0x2e,0x1c,0xa6,0xb4,0xc6,0xe8,0xdd,0x74,0x1f,0x4b,0xbd,0x8b,0x8a,
		0x70,0x3e,0xb5,0x66,0x48,0x03,0xf6,0x0e,0x61,0x35,0x57,0xb9,0x86,0xc1,0x1d,0x9e,
		0xe1,0xf8,0x98,0x11,0x69,0xd9,0x8e,0x94,0x9b,0x1e,0x87,0xe9,0xce,0x55,0x28,0xdf,
		0x8c,0xa1,0x89,0x0d,0xbf,0xe6,0x42,0x68,0x41,0x99,0x2d,0x0f,0xb0,0x54,0xbb,0x16};
	unsigned char temp,temp1,temp2,temp3,temp4;
	int Nb = 4;
	int Nk = 4;
	int Nr = 10;
	int i = 0;

	w[0]  = key[0][0];
	w[1]  = key[1][0];
	w[2]  = key[2][0];
	w[3]  = key[3][0];
	w[4]  = key[0][1];
	w[5]  = key[1][1];
	w[6]  = key[2][1];
	w[7]  = key[3][1];
	w[8]  = key[0][2];
	w[9]  = key[1][2];
	w[10] = key[2][2];
	w[11] = key[3][2];
	w[12] = key[0][3];
	w[13] = key[1][3];
	w[14] = key[2][3];
	w[15] = key[3][3];

	i = 4*Nk;
	while(i < 4*Nb*(Nr+1)) {
		temp1 = w[i-4];
                temp2 = w[i-3];
                temp3 = w[i-2];
                temp4 = w[i-1];
		if (i % (4*Nk) == 0){
			//RotWord
			temp = temp1;
			temp1 = temp2;
			temp2 = temp3;
			temp3 = temp4;
			temp4 = temp;
			//SubWord
			temp1 = sbox[temp1];
			temp2 = sbox[temp2];
			temp3 = sbox[temp3];
			temp4 = sbox[temp4];
			//Rcon
			temp1 = temp1 ^ Rcon[i/(4*Nk)];
			temp2 = temp2 ^ 0;
		        temp3 = temp3 ^ 0;
			temp4 = temp4 ^ 0;
		}
		else if (Nk > 6 && (i%Nk) == 4){
			//SubWord
			temp1 = sbox[temp1];
			temp2 = sbox[temp2];
			temp3 = sbox[temp3];
			temp4 = sbox[temp4];
		}
		w[i]=w[i-4*Nk]^temp1;
		w[i+1]=w[i-4*Nk+1]^temp2;
		w[i+2]=w[i-4*Nk+2]^temp3;
		w[i+3]=w[i-4*Nk+3]^temp4;
		i=i+4;
	}
}

/*
void inv_sb(){
  unsigned char inv_s[256] =
	{ 0x52,0x09,0x6A,0xD5,0x30,0x36,0xA5,0x38,0xBF,0x40,0xA3,0x9E,0x81,0xF3,0xD7,0xFB,
    0x7C,0xE3,0x39,0x82,0x9B,0x2F,0xFF,0x87,0x34,0x8E,0x43,0x44,0xC4,0xDE,0xE9,0xCB,
    0x54,0x7B,0x94,0x32,0xA6,0xC2,0x23,0x3D,0xEE,0x4C,0x95,0x0B,0x42,0xFA,0xC3,0x4E,
    0x08,0x2E,0xA1,0x66,0x28,0xD9,0x24,0xB2,0x76,0x5B,0xA2,0x49,0x6D,0x8B,0xD1,0x25,
    0x72,0xF8,0xF6,0x64,0x86,0x68,0x98,0x16,0xD4,0xA4,0x5C,0xCC,0x5D,0x65,0xB6,0x92,
    0x6C,0x70,0x48,0x50,0xFD,0xED,0xB9,0xDA,0x5E,0x15,0x46,0x57,0xA7,0x8D,0x9D,0x84,
    0x90,0xD8,0xAB,0x00,0x8C,0xBC,0xD3,0x0A,0xF7,0xE4,0x58,0x05,0xB8,0xB3,0x45,0x06,
    0xD0,0x2C,0x1E,0x8F,0xCA,0x3F,0x0F,0x02,0xC1,0xAF,0xBD,0x03,0x01,0x13,0x8A,0x6B,
    0x3A,0x91,0x11,0x41,0x4F,0x67,0xDC,0xEA,0x97,0xF2,0xCF,0xCE,0xF0,0xB4,0xE6,0x73,
    0x96,0xAC,0x74,0x22,0xE7,0xAD,0x35,0x85,0xE2,0xF9,0x37,0xE8,0x1C,0x75,0xDF,0x6E,
    0x47,0xF1,0x1A,0x71,0x1D,0x29,0xC5,0x89,0x6F,0xB7,0x62,0x0E,0xAA,0x18,0xBE,0x1B,
    0xFC,0x56,0x3E,0x4B,0xC6,0xD2,0x79,0x20,0x9A,0xDB,0xC0,0xFE,0x78,0xCD,0x5A,0xF4,
    0x1F,0xDD,0xA8,0x33,0x88,0x07,0xC7,0x31,0xB1,0x12,0x10,0x59,0x27,0x80,0xEC,0x5F,
    0x60,0x51,0x7F,0xA9,0x19,0xB5,0x4A,0x0D,0x2D,0xE5,0x7A,0x9F,0x93,0xC9,0x9C,0xEF,
    0xA0,0xE0,0x3B,0x4D,0xAE,0x2A,0xF5,0xB0,0xC8,0xEB,0xBB,0x3C,0x83,0x53,0x99,0x61,
    0x17,0x2B,0x04,0x7E,0xBA,0x77,0xD6,0x26,0xE1,0x69,0x14,0x63,0x55,0x21,0x0C,0x7D
  };

	state11=inv_s[state11];
	state12=inv_s[state12];
	state13=inv_s[state13];
	state14=inv_s[state14];
	state21=inv_s[state21];
	state22=inv_s[state22];
	state23=inv_s[state23];
	state24=inv_s[state24];
	state31=inv_s[state31];
	state32=inv_s[state32];
	state33=inv_s[state33];
	state34=inv_s[state34];
	state41=inv_s[state41];
	state42=inv_s[state42];
	state43=inv_s[state43];
	state44=inv_s[state44];
}

void inv_sr(){
	unsigned char tmp;

	state11=state11;
	state12=state12;
	state13=state13;
	state14=state14;
	tmp=state21;
	state21=state24;
	state24=state23;
	state23=state22;
	state22=tmp;
	tmp=state31;
	state31=state33;
	state33=tmp;
	tmp=state32;
	state32=state34;
	state34=tmp;
	tmp=state41;
	state41=state42;
	state42=state43;
	state43=state44;
	state44=tmp;
}

void inv_mc() {
	 unsigned char
	 tmp11,tmp12,tmp13,tmp14,tmp21,tmp22,tmp23,tmp24,
	 tmp31,tmp32,tmp33,tmp34,tmp41,tmp42,tmp43,tmp44;

	tmp11=gmul(state11,14)^gmul(state21,11)^gmul(state31,13)^gmul(state41,9);
	tmp21=gmul(state11,9)^gmul(state21,14)^gmul(state31,11)^gmul(state41,13);
	tmp31=gmul(state11,13)^gmul(state21,9)^gmul(state31,14)^gmul(state41,11);
	tmp41=gmul(state11,11)^gmul(state21,13)^gmul(state31,9)^gmul(state41,14);
	tmp12=gmul(state12,14)^gmul(state22,11)^gmul(state32,13)^gmul(state42,9);
	tmp22=gmul(state12,9)^gmul(state22,14)^gmul(state32,11)^gmul(state42,13);
	tmp32=gmul(state12,13)^gmul(state22,9)^gmul(state32,14)^gmul(state42,11);
	tmp42=gmul(state12,11)^gmul(state22,13)^gmul(state32,9)^gmul(state42,14);
	tmp13=gmul(state13,14)^gmul(state23,11)^gmul(state33,13)^gmul(state43,9);
	tmp23=gmul(state13,9)^gmul(state23,14)^gmul(state33,11)^gmul(state43,13);
	tmp33=gmul(state13,13)^gmul(state23,9)^gmul(state33,14)^gmul(state43,11);
	tmp43=gmul(state13,11)^gmul(state23,13)^gmul(state33,9)^gmul(state43,14);
	tmp14=gmul(state14,14)^gmul(state24,11)^gmul(state34,13)^gmul(state44,9);
	tmp24=gmul(state14,9)^gmul(state24,14)^gmul(state34,11)^gmul(state44,13);
	tmp34=gmul(state14,13)^gmul(state24,9)^gmul(state34,14)^gmul(state44,11);
	tmp44=gmul(state14,11)^gmul(state24,13)^gmul(state34,9)^gmul(state44,14);

	state11=tmp11;
	state12=tmp12;
	state13=tmp13;
	state14=tmp14;
	state21=tmp21;
	state22=tmp22;
	state23=tmp23;
	state24=tmp24;
	state31=tmp31;
	state32=tmp32;
	state33=tmp33;
	state34=tmp34;
	state41=tmp41;
	state42=tmp42;
	state43=tmp43;
	state44=tmp44;
}

*/
