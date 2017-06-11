#include <bits/stdc++.h>
#include <random>
using namespace std;

/*
[+] Author Adilson Luis Jonck Junior, UDESC, 2017
*/

typedef string BigInt;
int const numero_tentativas = 200;
int const max_primo = 999999;

int geraPrimoPequeno(int min, int max){
	bitset<max_primo> primo;

	primo.set();
	primo[0] = primo[1] = 0;
	for(int i = 2; i < max; i++){
		if(primo[i]){
			for(int j = i + i; j < max; j+=i)
				primo[j] = 0;
		}
	}
	random_device rd;
	mt19937 mt(rd());
	uniform_int_distribution<> distribution(min,max);
	int rand_prim = distribution(mt);
	while(primo.test(rand_prim) == 0) rand_prim = distribution(mt);
	return rand_prim;
}


bool IsBigger(BigInt a, BigInt b){
	if(a.size() > b.size()) return true;
	else if(a.size() < b.size()) return false;
	else{
		for(int i = 0; i < a.size(); i++){
			if(a[i] > b[i]) return true;
			else if(a[i] < b[i]) return false;
		}
	}
	return true;
}

bool isPositive(BigInt a){
	return a[0] != '-';
}

bool isNegative(BigInt a){
	return a[0] == '-';
}

BigInt addBigInt(BigInt a, BigInt b){
	int mini = min(a.size(), b.size()), na, nb, soma, rem;
	rem = 0;
	reverse(a.begin(),a.end());
	reverse(b.begin(),b.end());
	BigInt novoBig;
	for(int i = 0; i < mini; i++){
		na = a[i]-'0', nb = b[i]-'0';
		soma = na + nb + rem;
		if(soma>9){
			novoBig.push_back((soma%10)+'0');
			rem = soma/10;
		}
		else{
			novoBig.push_back(soma+'0');
			rem = 0;
		}
	}
	if(a.size() > b.size()){
		for(int i = mini; i < a.size(); i++){
			na = a[i]-'0';
			soma = na + rem;
			if(soma>9){
				novoBig.push_back((soma%10)+'0');
				rem = soma/10;
			}
			else{
				novoBig.push_back(soma+'0');
				rem = 0;
			}
		}
	}
	else{
		for(int i = mini; i < b.size(); i++){
			nb = b[i]-'0';
			soma = nb + rem;
			if(soma>9){
				novoBig.push_back((soma%10)+'0');
				rem = soma/10;
			}
			else{
				novoBig.push_back(soma+'0');
				rem = 0;
			}
		}
	}
	if(rem) novoBig.push_back(rem+'0');
	reverse(novoBig.begin(), novoBig.end());
	return novoBig;
}

BigInt MulBigInt(BigInt a, BigInt b){
	BigInt novoBig;
	int rem = 0, soma = 0;
	reverse(a.begin(), a.end());
	reverse(b.begin(), b.end());
	vector<BigInt> rs;
	for(int i = 0; i < b.size(); i++){
		novoBig = "";
		rem = 0;
		for(int j = 0; j < a.size(); j++){
			soma = (a[j]-'0')*(b[i]-'0') + rem;
			if(soma>9){
				novoBig.push_back((soma%10)+'0');
				rem = soma/10;
			}
			else{
				novoBig.push_back(soma+'0');
				rem = 0;
			}
		}
		if(rem) novoBig.push_back(rem+'0');
		reverse(novoBig.begin(), novoBig.end());
		for(int k = 0; k < i; k++)
			novoBig.push_back('0');
		rs.push_back(novoBig);
	}
	novoBig = "0";
	for(int i = 0; i < rs.size(); i++)
		novoBig = addBigInt(novoBig, rs[i]);
	return novoBig;
}

BigInt SubtractBigInt(BigInt a, BigInt b){
	BigInt maior,menor, novoBig;
	if(IsBigger(a,b)) maior = a, menor = b;
	else	  		  maior = b, menor = a;
	reverse(a.begin(), a.end());
	reverse(b.begin(), b.end());
	reverse(maior.begin(), maior.end());
	reverse(menor.begin(), menor.end());
	int mini = min(maior.size(), menor.size());


	for(int i = 0; i < mini; i++){
		int na = maior[i]-'0', nb = menor[i]-'0';
		//printf("na = %d, nb = %d\n",na,nb);
		if(na >= nb){
			novoBig.push_back(na-nb+'0');
			//printf("colocando %d\n",na-nb);
		}
		else{
			maior[i+1] = maior[i+1] - 1;
			na+=10;
			novoBig.push_back(na-nb+'0');
			//printf("colocando %d\n",na-nb);
		}
	}
	if(IsBigger(a,b)){
		for(int i = mini; i < a.size(); i++)
			novoBig.push_back(maior[i]);
	}
	else{
		for(int i = mini; i < b.size(); i++)
			novoBig.push_back(maior[i]);	
	}
	//printf("Novo big = %s\n",novoBig.c_str());
	
	for(int i = novoBig.size() -1 ; i >= 0 ; i--){
		//printf("Analisando %c\n",novoBig[i]);
		if(novoBig[i] == '0' && novoBig.size() != 1) novoBig.pop_back();
		else{break;}
	}

	reverse(novoBig.begin(), novoBig.end());

	return novoBig;
}



BigInt addBigInteger(BigInt a, BigInt b){
	if(isPositive(a) && isPositive(b)){
		return addBigInt(a,b);
	}
	if(isPositive(a) && isNegative(b)){
		BigInt nb(b.begin()+1, b.end());
		if(IsBigger(nb,a)){
			string res = SubtractBigInt(a,nb);
			if(res != "0") return "-"+res;
			else		   return res;
		}
		else			  return SubtractBigInt(a,nb);
	}
	if(isNegative(a) && isPositive(b)){
		BigInt na(a.begin()+1, a.end());
		if(IsBigger(na,b)){
			string res = SubtractBigInt(na,b);
			if(res != "0") return "-"+res;
			else		   return res;
		}
		else			  return SubtractBigInt(na,b);
	}
	if(isNegative(a) && isNegative(b)){
		BigInt na(a.begin()+1, a.end());
		BigInt nb(b.begin()+1, b.end());
		return "-"+addBigInt(na,nb);
	}
}

BigInt SubtractBigInteger(BigInt a, BigInt b){
	if(isPositive(a) && isPositive(b)){
		if(IsBigger(a,b)) return SubtractBigInt(a,b);
		else			  return "-"+SubtractBigInt(a,b);
	}
	if(isPositive(a) && isNegative(b)){
		BigInt nb(b.begin()+1, b.end());
		return addBigInt(a,nb);
	}
	if(isNegative(a) && isPositive(b)){
		BigInt na(a.begin()+1, a.end());
		return "-"+addBigInt(na,b);
	}
	if(isNegative(a) && isNegative(b)){
		BigInt na(a.begin()+1, a.end());
		BigInt nb(b.begin()+1, b.end());
		if(IsBigger(nb,na)) return SubtractBigInt(nb,na);
		else				return "-"+SubtractBigInt(nb,na);
	}
}

BigInt MulBigInteger(BigInt a, BigInt b){
	if(a == "0" || b == "0") return "0";
	if(isPositive(a) && isPositive(b))
		return MulBigInt(a,b);
	else if(isPositive(a) && isNegative(b)){
		BigInt nb(b.begin()+1, b.end());
		return "-"+MulBigInt(a,nb);
	}
	else if(isNegative(a) && isPositive(b)){
		BigInt na(a.begin()+1, a.end());
		return "-"+MulBigInt(na, b);
	}
	else if(isNegative(a) && isNegative(b)){
		BigInt na(a.begin()+1, a.end());
		BigInt nb(b.begin()+1, b.end());
		return MulBigInt(na,nb);
	}
}

pair<BigInt,BigInt> DivideBigInt(BigInt a, BigInt b){
	if(b == "0"){printf("DIVISAO POR 0\n");exit(0);}
	if(a == "0") return make_pair("0","0");
	BigInt res = "0", div = b;

	while(IsBigger(a,b)){
		BigInt aux = "1";
		while(IsBigger(a,div)){
			div += "0";
			aux += "0";
		}
		div.pop_back();
		aux.pop_back();
		res = addBigInteger(res, aux);
		a = SubtractBigInteger(a,div);
		div = b;
	}
	return make_pair(res,res);
}

BigInt DivideBigInteger(BigInt a, BigInt b){
	if(isPositive(a) && isPositive(b)){
		return DivideBigInt(a,b).first;
	}
	else if(isPositive(a) && isNegative(b)){
		BigInt nb(b.begin()+1, b.end());
		BigInt res = DivideBigInt(a,nb).first;
		if(res == "0") return res;
		else return "-"+res;
	}
	else if(isNegative(a) && isPositive(b)){
		BigInt na(a.begin()+1, a.end());
		BigInt res = DivideBigInt(na, b).first;
		if(res == "0") return res;
		else return "-"+res;
	}
	else if(isNegative(a) && isNegative(b)){
		BigInt na(a.begin()+1, a.end());
		BigInt nb(b.begin()+1, b.end());
		return DivideBigInt(na,nb).first;
	}
}

BigInt ModuloBigInteger(BigInt a, BigInt b){
	BigInt res, adivb;
	//printf("(%s %s)\n",a.c_str(), b.c_str());
	adivb = DivideBigInteger(a,b);
	//printf("div %s\n",adivb.c_str());
	adivb = MulBigInteger(adivb, b);
	//printf("mul %s\n",adivb.c_str());
	res = SubtractBigInteger(a, adivb);
	//printf("Modulo %s %s = %s\n",a.c_str(), b.c_str(), res.c_str());
	return res;
}

BigInt gcdBigInteger(BigInt a, BigInt b){
	if(b == "0") return a;
	else return gcdBigInteger(b, ModuloBigInteger(a,b));
}

pair< BigInt, pair<BigInt,BigInt> > ExtendedEuclides(BigInt a, BigInt b){
	if(b == "0") return make_pair(a, make_pair("1","0"));
	pair<BigInt, pair<BigInt,BigInt> > triple, triple2;
	triple = ExtendedEuclides(b, ModuloBigInteger(a,b));
	BigInt d = triple.first,y = triple.second.second,x = triple.second.first;
	BigInt adivb = DivideBigInteger(a,b);
	BigInt mulans = MulBigInteger(adivb, y);
	triple2 = make_pair(d, make_pair(y, SubtractBigInteger(x,mulans)   )  );
	return triple2;
}

BigInt ExponentiationBigInteger(BigInt a, BigInt b){
	if(b == "0") return "1";
	BigInt novoBig = a;
	for(BigInt i = "1"; i != b; i = addBigInteger(i, "1")){
		novoBig = MulBigInteger(novoBig, a);
	}
	return novoBig;
}

BigInt ExpoModularBigInteger(BigInt base, BigInt expo, BigInt mod){
	BigInt res = "1";
	base = ModuloBigInteger(base, mod);
	while(IsBigger(expo, "0") && expo != "0"){
		if(ModuloBigInteger(expo, "2")  == "1")
			res = ModuloBigInteger(MulBigInteger(res, base),mod);
		//printf("%s %s %s\n",base.c_str(), expo.c_str(), mod.c_str());
		expo = DivideBigInteger(expo, "2");
		base = ModuloBigInteger(MulBigInteger(base,base), mod);
	}
	return res;
}

BigInt ModLinSolver(BigInt a, BigInt b, BigInt n){
	//printf("(%s, %s ,%s)\n",a.c_str(), b.c_str(), n.c_str());
	//printf("Extended de (%s,%s)\n",a.c_str(), n.c_str());
	pair<BigInt, pair<BigInt,BigInt> > triple = ExtendedEuclides(a,n);
	BigInt d=triple.first,xl=triple.second.first,yl=triple.second.second;
	//printf("(%s,%s,%s)\n",d.c_str(), xl.c_str(), yl.c_str());
	BigInt porra = ModuloBigInteger(d,b);
	BigInt porra2 = ModuloBigInteger(b,d);
	if( porra == "0" || porra2 == "0"){
		BigInt xo = ModuloBigInteger(MulBigInteger(xl, DivideBigInteger(b,d)),n);
		BigInt dminus = SubtractBigInteger(d, "1");
		//printf("modlin d=%s\n",d.c_str());
		BigInt ans;
		for(BigInt i = "0"; IsBigger(dminus, i); i = addBigInteger(i, "1")){
			BigInt muls = MulBigInteger(i, DivideBigInteger(n,d));
			ans = ModuloBigInteger( addBigInteger(xo, muls), n );
			if(ans[0] != '-') return ans;
		}
		return ans;
	}
	else{
		printf("NO SOLUTION TO MODLINSOLVER %s %s %s\n",a.c_str(), b.c_str(), n.c_str());
		exit(0);
	}
}


bool primoProvavel(BigInt num, int num_testes){
	if(num == "2") return true;
	if(num == "1" || num == "0") return false;
	for(int i = 0; i < num_testes; i++){
		random_device rd;
		mt19937 mt(rd());
		uniform_int_distribution<long long> distribution(2,stoi(num));
		BigInt rand_prim = to_string(distribution(mt));
		while((IsBigger(num, rand_prim) && ModuloBigInteger(num, rand_prim) == "0") ||
		      (IsBigger(rand_prim, num) && ModuloBigInteger(rand_prim, num) == "0"))
			rand_prim = to_string(distribution(mt));
		string res = ExpoModularBigInteger(rand_prim, SubtractBigInteger(num, "1"), num);
		if(res != "1") return false;
	}
	return true;
}

BigInt FindRoot(BigInt n){
	BigInt low = "0", high = n, mid, mid2;
	while(IsBigger(high, low)){
		mid = addBigInteger(low,high);
		mid = DivideBigInteger(mid, "2");
		mid2 = MulBigInteger(mid,mid);
		if(mid2 == n) return mid;
		if(IsBigger(mid2, n))
			high = SubtractBigInteger(mid, "1");
		else
			low = addBigInteger(mid, "1");
	}
}

void ataqueForcaBrutaBigInt(string msg, int ei, BigInt n){
	BigInt e = to_string(ei);
	BigInt root_N = FindRoot(n);
	printf("root_n = %s\n",root_N.c_str());
	for(BigInt i = root_N; IsBigger(i, "1"); i = SubtractBigInteger(i, "1")){
		for(BigInt j = root_N; IsBigger(n, j); j =addBigInteger(j, "1")){
			printf("Testando %s e %s\n",i.c_str(), j.c_str());
			if(MulBigInteger(i,j) == n && primoProvavel(i, numero_tentativas) && primoProvavel(j, numero_tentativas))
				cout << "POSSIVEL SOLUÇÃO: " << i << " E " << j << endl;
		}
	}
}

BigInt ataqueForcaBruta(BigInt ex, BigInt n){
	printf("\x1b[31m" "[+] HACKING NASA, PLEASE WAIT ." "\x1b[0m" "\n");
	bitset<max_primo> primo;
	primo.set();
	primo[0] = primo[1] = 0;
	vector<int> primes;
	for(int i = 2; i < max_primo; i++){
		if(primo[i]){
			primes.push_back(i);
			for(int j = i + i; j < max_primo; j+=i)
				primo[j] = 0;
		}
	}
	BigInt root_N = FindRoot(n);
	vector<int>::iterator it2 = lower_bound(primes.begin(), primes.end(), stoi(root_N));

	//vector<int>::iterator it2 = primes.end();
	BigInt big_first, big_second;
	int found = 0;
	for(vector<int>::iterator it = primes.begin(); it != it2 && !found; it++){
		int first = *it;
		big_first = to_string(first);
		if(ModuloBigInteger(n, big_first) == "0"){
			big_second = DivideBigInteger(n, big_first);
			found = 1;
		}
	}
	big_first = SubtractBigInteger(big_first, "1");
	big_second = SubtractBigInteger(big_second, "1");
	printf("\x1b[32m" "[+] ACESS GRANTED ." "\x1b[0m" "\n\n");
	return ModLinSolver(ex,"1",MulBigInteger(big_first, big_second));
}
