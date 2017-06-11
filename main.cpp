#include <bits/stdc++.h>
#include <random>
#include <ctime>
#include "bigint.cpp"
using namespace std;
#define bit(i) (1<<(i))
/*
[+] Author Adilson Luis Jonck Junior, UDESC, 2017
*/
int p, q, pqmenos, low=100000, high=999999, e, tam_bloco = 4;
pair<BigInt,BigInt> public_key, private_key;
BigInt n, pqminus, d, bp, bq;

void start_variables(){
	d = "-1";
	while(isNegative(d)){
		p = geraPrimoPequeno(low,high);
		q = geraPrimoPequeno(low,high);
		bp = to_string(p), bq = to_string(q);
		n = MulBigInteger(bp, bq);
		pqminus = MulBigInteger(SubtractBigInteger(bp,"1"), SubtractBigInteger(bq,"1"));
		e = geraPrimoPequeno(1000, 9999);
		d = ModLinSolver(to_string(e),"1",pqminus);
	}
}

string read_input(){
	string linha, entrada;
	while(getline(cin, linha)) entrada += linha + '\n';
	//string entrada = "adam mews dos santos";
	return entrada;
}

pair<BigInt, BigInt> create_public_key(){
	pair<BigInt, BigInt> public_key;
	public_key.first = to_string(e);
	public_key.second = n;
	return public_key;
}

pair<BigInt, BigInt> create_private_key(){
	pair<BigInt, BigInt> private_key;
	private_key.first = d;
	private_key.second = n;
	return private_key;
}

vector<string> encrypt_message(string entrada, BigInt ex, BigInt nx){
	vector<string> msg_encrypt;
	for(int i = 0; i < entrada.size(); i += tam_bloco){
		//printf("i vale %d e t vale %d\n",i, tam_bloco);
		string bloco = "";
		for(int j = i; j < min((int)entrada.size(), i + tam_bloco); j++)
			bloco += entrada[j];
		//bloco = entrada.substr(i, i+tam_bloco+1);
		//printf("string %s\n",bloco.c_str());
		int res = 0;
		char bytes[4] = {0};
		for(int j = 0; j < bloco.size(); j++){
			bytes[j] = bloco[j];
		}
		
		res = res | (bytes[0] << 24);
		res = res | (bytes[1] << 16);
		res = res | (bytes[2] << 8);
		res = res | bytes[3];

		BigInt bres = to_string(res);
		BigInt cryp_bloco = ExpoModularBigInteger(bres, ex, nx);
		msg_encrypt.push_back(cryp_bloco);
	}
	cout << endl;
	return msg_encrypt;
}

string decrypt_message(vector<string> msg_encrypt, BigInt dx, BigInt nx){
	string ans = "";
	for(int i = 0; i < msg_encrypt.size(); i++){
		BigInt bloco = msg_encrypt[i];
		BigInt decryp = ExpoModularBigInteger(bloco, dx, nx);
		int mensagem = stoi(decryp);
		//for(int bit = 31; bit >= 0; bit--) printf("%d", mensagem&(1<<bit) ? 1: 0);
		//printf("Vendo bloco %d = %d\n",i,mensagem);
		char byte4 = mensagem&0x000000ff;
		char byte3 = ((mensagem&0x0000ff00) >> 8);
		char byte2 = ((mensagem&0x00ff0000) >> 16);
		char byte1 = ((mensagem&0xff000000) >> 24);
		if(byte1) ans += byte1;
		if(byte2) ans += byte2;
		if(byte3) ans += byte3;
		if(byte4) ans += byte4;	
	}
	return ans;
}

int main(){
  int overflow = 0x55AACCFF;
	start_variables();
	ofstream original, criptografado, brute, publico, privado;
	original.open("original.txt");

	string entrada = read_input();
	original << entrada;
	original.close();

	criptografado.open("criptografado.txt");



	pair<BigInt, BigInt> public_key = create_public_key();
	pair<BigInt, BigInt> private_key = create_private_key();
	publico.open("public.txt");
	publico << "Public key : <" << public_key.first << ", " << public_key.second << "> (e,n)" << endl;
	privado << "Private key : <" << private_key.first << ", " << private_key.second << "> (d,n)" << endl;
	vector<string> vs = encrypt_message(entrada, public_key.first, public_key.second);
	publico.close();
	privado.close();
	for(int i = 0; i < vs.size(); i++){
		criptografado << vs[i] << endl;
	}
	criptografado.close();

	brute.open("brute.txt");

	BigInt ansBrute = ataqueForcaBruta(public_key.first, public_key.second);
	brute << ansBrute << endl;
	brute << decrypt_message(vs, ansBrute, public_key.second) << endl;

}
