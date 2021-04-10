#include <bits/stdc++.h>
#include "encode.h"

using namespace std;

#define N_block 5000000
unsigned char input[N_block<<4];
unsigned char output[N_block<<4];
unsigned char IV[16] = {255,255,255,255,255,255,255,255,0,0,0,0,0,0,0,0};
unsigned char key[16] = {255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255};
unsigned char expandedKey[176];

void readKey(char * input_name){
	//lay key
	string str;
	ifstream infile;
	infile.open("keyfile", ios::in | ios::binary);
	if (infile.is_open()){
		getline(infile, str);
		infile.close();
	}
	else cout << "Open keyfile error!";

	istringstream hex_chars_stream(str);
	int i = 0;
	unsigned int c;
	while (hex_chars_stream >> hex >> c){
		key[i] = c;
		i++;
	}
	
	//expandedKey
	KeyExpansion(key, expandedKey);
}

void counter(){
	int i = 15;
	while(i != -1){
		if(IV[i] == 255){
			IV[i] = 0;
			i--;
		}
		else{
			IV[i]++;
			break;
		}
	}
}

int main(int argc, char **argv){
	clock_t s = clock();
	
    unsigned long long dung_luong = 0;
    fstream fin, fout;
	char *input_file = "e_inp.txt", *output_file = "cipher.txt";
	if(argc > 1){
		input_file = argv[1];
	}
	// tinh dung luong
    FILE *fp;
    fp = fopen(input_file, "rb");
    fseek(fp, 0, SEEK_END);
    dung_luong = ftell(fp);
    fclose(fp);
    fin.open(input_file, ios::in | ios::binary);
    fout.open(output_file, ios::out | ios::binary);
    
    //mo rong khoa
    readKey(input_file);
    // lay IV
    for(int i = 0; i != 16; i++){
        char c;
        fin.get(c);
        IV[i] = c;
    }
    int n = dung_luong - 16;//16 byte IV
    unsigned char *in;
    unsigned char *out;
    unsigned char outASE[16];
    while(!fin.eof()){
    	
    	fin.read((char*)input, sizeof(input));
    	int len = 0;
    	int len_dt = 0;
        if(n >= N_block<<4){
            len = N_block<<4;
            len_dt = N_block<<4;
            n = n - N_block<<4;
        }
        else{
            len = (n/16 + 1)<<4;
            len_dt = n;
        }
        
        for(int i = 0; i != len; i += 16){
        	AESEncrypt(IV, expandedKey, outASE);
        	out = output + i;
        	in = input + i;
        	for(int j = 0; j != 16; j++){
        		out[j] = in[j] ^ outASE[j];
			}
			//tang IV
        	counter();
		}
		
		fout.write((char*)output, len_dt);
	}
	
	clock_t e = clock();
	fin.close();
	fout.close();
	cout<<"\nDung luong file giai ma: "<<dung_luong<<" bytes\n";
	cout<<"Thoi gian giai ma: "<<(double)(e-s)/CLOCKS_PER_SEC<< " second (s)\n";
	return 0;
}
