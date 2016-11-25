#include <iostream>
#include<vector>
#include <string>
#include <fstream>
#include <cstdlib>
#include <set>
#include <functional>
#include <cmath>
using namespace std;
//cstdlib es per random xD
#include <chrono>



#define t_numdeminhash 50
#define k 3
#define numtaules 50
#define ranghash 0x000FFFFF

//minimo de signatura
int MINSIGNATURA;
int MAXSIGNATURA;
vector< vector < vector<bool> > > signatures;
vector<set<unsigned int>  > documents;
vector<int> hash_xor_values(numtaules);
vector<float> jacobianas;
int NUM_DOCS;
vector<string> nomdocs;
vector<int> numsingles;



class Timer
{
public:
    Timer() : beg_(clock_::now()) {}
    void reset() { beg_ = clock_::now(); }
    double elapsed() const { 
        return std::chrono::duration_cast<second_>
            (clock_::now() - beg_).count(); }

private:
    typedef std::chrono::high_resolution_clock clock_;
    typedef std::chrono::duration<double, std::ratio<1> > second_;
    std::chrono::time_point<clock_> beg_;
};




int randomint(){//retorna un random entre 0 i 2³¹
	//srand(time(NULL));
	//cout << "max:"<< RAND_MAX << endl;//2³¹ - 1
	//cout << "min :0" << endl;	
	return rand();
}

//aquesta va de ma amb comparacio_hashes
int com_semblants(vector<bool> prim, vector<bool> seg){
	int eresante=0;	
	for(int i =0;i< prim.size();i++){
			if(prim[i] && seg[i])eresante ++;
	}
	return eresante;
}


//Pre:sign1 i sign2 tenen la mateixa llargada i amplada
//post retorna la quantitat de semblances entre la signatura de dos documents(matriu de booleans)
void sim(vector<vector<bool> >  & sign1, vector < vector<bool> > & sign2,vector<int> & result ){
	for(int i= 0;i<sign1.size();i++){
			//cout << "hai" << endl;
			result[i]=com_semblants(sign1[i], sign2[i]);
			//cout << result[i] << endl;
	}
}

int myhash(string s){
    hash<string> hasher;
    return hasher(s);
}


//pre: le pasas el "&nombredelfichero[0]" y un set vacio
//post: guarda en mochila todos los k-shigles en hashcode del doc con el nombre q le pasas de parametro y actualiza el MINSIGNATURA
void readFile(char *target, set<unsigned int>  *mochila){
    //cout << "entra al readfile" << endl;
    ifstream file;
    file.open (target);
    if (!file.is_open()) return;
	string word;
	string var;
	int max = 0;
	bool top = false;
	int pick;
	int chosed;
	
	while (!top){
		//cout << "entra al primer bucle" << endl;
		pick = 0;
		//chosed = randomint();//gillrandom(0,random);
		//cout<<"RANDOM "<<chosed<<endl;
		//cout << chosed << endl;
		/*for(int i = 0; i<chosed and !top;++i){
			//cout << "entra al for del primer bucle" << endl;
			file >> var;
			if(!file.eof())max++;
			else{
				file.clear();
				file.seekg(0, ios::beg);
				top = true;
			}
		}*/
		word= "";
		while(pick < k and !top){
			//cout << "entra al primer bucle primer while" << endl;
			file >> var;
			if(pick != 0)word += " ";
			word += var;
			pick++;
			if(!file.eof())max++;
			else{
			  //cout << "hey oh lets go" << endl;
				file.clear();
				file.seekg(0, ios::beg);
				top = true;
			}
        }if (pick == k)mochila->insert(myhash(word));//cout << word << "    por el 1º" << endl;//guarda var;
				//cout<<"1putos  "<< mochila->size()<<endl;  
	}
	////float conversion = max*0.05;
	////int t_numdeminhash = int(conversion + 0.5);
	//cout<<"top = "<<top<<"  max = "<<max<< endl;
	for(int i = 1; i<k;++i){
		//cout << "segon while inside" << endl;
		file.clear();
		file.seekg(0, ios::beg);
		for(int j = 0; j<i;++j){
			file >> var;
		}
		/////chosed = randomint()%(max-k);//gillrandom(0, max-5);
		//cout<<"RANDOM "<<chosed<<endl;
		//cout << "inicial " << act << endl;
		/////for(int i = 0; i<chosed;++i) file >> var;
		
		while(!file.eof()){
			word= "";
			pick = 0;
			while(pick < k){
				file >> var;
				if(pick != 0)word += " ";
				word += var;
				pick++;
				if(file.eof() and pick<k) pick +=2*k;
				//cout  << " tira2" <<endl<< word<< endl;
			}//cout << word << "    por el 2º" << endl;//guarda var;
            if(pick == k)mochila->insert(myhash(word));
			//cout<<"2putos  "<< word<<endl;
			//cout<< mochila->size()<<endl;
		}
	}
	if(MINSIGNATURA == -1 or MINSIGNATURA > mochila->size()) MINSIGNATURA = mochila->size();
	  if(MAXSIGNATURA < mochila->size()) MAXSIGNATURA = mochila->size();
	  numsingles.push_back(mochila->size());
}

										 
										 
//Post: se le han quitado valores random a mochila asta tener MNSIUTURA valores									 
void borrarandoms(set<unsigned int>  *mochila){
	  int die;	
	  while(MINSIGNATURA < mochila->size()){
	  //cout << "entra al if raro" << endl;
	  	die = randomint()%mochila->size();
        set<unsigned int> ::iterator it;
	  	it = mochila->begin();
	  	for(int h = 1; h<die; ++h){
	    	//cout << "entra al for dins del if raro" << endl;
	    	++it;
	  	}
	  	mochila->erase(it);
	}
}
	/*//cout << "busco " << t_numdeminhash << endl;
	while(mochila->size() <t_numdeminhash){
		//cout << "segon while inside" << endl;
		file.clear();
		file.seekg(0, ios::beg);
		pick = 0;
		chosed = randomint()%(max-k);//gillrandom(0, max-5);
		//cout<<"RANDOM "<<chosed<<endl;
		//cout << "inicial " << act << endl;
		for(int i = 0; i<chosed;++i) file >> var;
		word= "";
		while(pick < k){
			file >> var;
			if(pick != 0)word += " ";
			word += var;
			pick++;
			//cout  << " tira2" <<endl<< word<< endl;
		}//cout << word << "    por el 2º" << endl;//guarda var;
		mochila->insert(word);
		//cout<<"2putos  "<< word<<endl;
		//cout<< mochila->size()<<endl;

	}
	//cout << max<< endl;
}*/

//Pre: k-shingles de dos docs a A i els altres a B
//Post: Retorna el modul de l'interseccio d'aquests sets
float opInterseccion(set<unsigned int>  *a, set<unsigned int>  *b) {
  set<unsigned int>  interseccion;
  set<unsigned int>  *mayor, *menor;
  set<unsigned int> ::iterator it;

  if (a->size() > b->size()) { 
    mayor = a; 
    menor = b; 
  } else { 
    mayor = b; 
    menor = a; 
  } 
  for (it = menor->begin(); it != menor->end(); it++) { 
    if (mayor->count(*it) > 0) { 
      interseccion.insert(*it); 
    } 
  } 

  return interseccion.size(); 
} 


//Pre: k-shingles de dos docs a A i els altres a B
//Post: Retorna el modul de l'unio d'aquests sets
float opUnion(set<unsigned int>  *a, set<unsigned int>  *b) {
  set<unsigned int>  unionSet;
  set<unsigned int> ::iterator it;

  for (it = a->begin(); it != a->end(); it++) { 
    unionSet.insert(*it); 
  } 

  for (it = b->begin(); it != b->end(); it++) { 
    if (unionSet.count(*it) == 0) { 
      unionSet.insert(*it); 
    } 
  } 

  return unionSet.size(); 
}


/*Pre: k-shingles de dos docs a A i els altres a B
  Post: Retorna el modul de l'interseccio entre el modul de l'union
	entre el set a i b*/
float Jsim (set<unsigned int>  *a, set<unsigned int>  *b) {
  float modulo_interseccion = opInterseccion(a,b);
  float modulo_union = opUnion(a,b);
  return ((modulo_interseccion)/(modulo_union));
}


//Pre: A conte els w k-shingles, n es un numero random
//Post: Retorna el set havent aplicat un xor entre cada posicio d'a i n
void xor_hash(set<unsigned int> * a, vector<bool>& s, int n) {
  set<unsigned int> ::iterator it;
  //vector<bool> result(a->size(),false);
  for (it = a->begin(); it!=a->end(); ++it) {
        int temp = *it;


    s[(temp ^ n)%s.size()] = true;
  }
  //return result;
}



//Pre: Entra el set despres del xor
//Post: Retorna un vector amb cada posicio a true o false depenent del modul del set inicial.
vector<bool> modul_xor(set<unsigned int>  *a){
  set<unsigned int> ::iterator it;
  vector<bool> a_retornar(a->size(),false);
  for(it = a->begin(); it != a->end(); ++it) {
    int module = *it % a->size();
    a_retornar[module] = true;
  }
  return a_retornar;
}

void print(set<unsigned int>  *a){
    cout << "imprimiendo sets" << endl;
  set<unsigned int> ::iterator it;
  for(it = a->begin(); it != a->end(); ++it) {
    cout << *it << endl;
    cout << *it%2 << endl;
  }
}


int main() {
    Timer t;
	srand(time(NULL));
	MINSIGNATURA=-1;
	MAXSIGNATURA = 0;
	string s1;
    documents=vector<set<unsigned int>  >(0);
	nomdocs=vector<string> (0);
	while(cin >> s1){
		///PARTE 1
	// Creem un nou set on tindrem la signatura del fitxer s1
        set<unsigned int>  nouset;
		//posem la signatura de s1(els valors de string hashejats)
		readFile(&s1[0], &nouset);
		//quan tenim el set l'afegim
		documents.push_back(nouset);
		//readfile actualitza el valor de MINSIGNATURA
		nomdocs.push_back(s1);
	}
	NUM_DOCS=documents.size();	
	jacobianas=vector<float>((NUM_DOCS-1),0);//compararem un amb tots

	
	//PARTE 2
	//Fem la comparació Jaccard ara perquè perderem precisió fent-la més tard
	for(int i=1;i<NUM_DOCS;i++){
        jacobianas[i-1]=Jsim(&documents[0],&documents[i]);
	}

	/*//PARTE 3
	for(int i= 0;i<NUM_DOCS;i++){
        borrarandoms(&documents[i]);
		//tornem tots els set del mateix tamany, ens és necessari per tal poder fer el MinHash+LSH
	}*/

		//PARTE 4 
		//es el moment de generar les signatures Minhash(matrius booleanes)
	//el primer índex és el document, el segon es el numero de funció i el tercer es el valor que s'ha hashejat
	
    //genera los num de las XOR
    for(int i = 0; i<numtaules;i++){
		hash_xor_values[i] = randomint();
	}

    signatures = vector<vector<vector<bool> > >(NUM_DOCS, (vector<vector<bool> >(numtaules, vector<bool>(ranghash , false))));
    cout << "tamany de signatures: " << signatures.size() << endl;
//            cout << nomdocs[i+1] << '\t' << jacobianas[i] << '\t';

    //print(&documents[0]);
	for(int d = 0; d<NUM_DOCS; ++d){
		for(int f = 0; f<numtaules;++f){
		  xor_hash(&documents[d],signatures[d][f],hash_xor_values[f]);
				
		}
	}



	
	
	//PARTE 5
	//ara comparem el document D1 amb [D2...DN] fent servir LSH
    vector<vector<int > > sim_taula(NUM_DOCS-1, vector<int>(numtaules));


    for(int i=0;i<NUM_DOCS-1; i++){
        sim(signatures[0],signatures[i+1],sim_taula[i]);
	}

	//PARTE 6
	//printem resultats
	cout << "document" << '\t' <<"Jsim" << '\t';
    for(int i= 0;i<numtaules;++i) cout << "hash" << i << '\t';
	cout << endl;
    for(int i=0;i<NUM_DOCS-1;i++){
        cout << nomdocs[i+1] << '\t' << jacobianas[i] << '\t';
        for(int j=0;j<numtaules;++j){
            cout << (float)sim_taula[i][j]/(float)max(numsingles[0],numsingles[i+1]) << '\t';//((float)sim_taula[i][j]/(float)ranghash) << '\t' << '\t';
		}
        cout << endl;
	}
    cout << "MINSIGNATURA"<< '\t'  << MINSIGNATURA << endl;
     cout << "MAXSIGNATURA"<< '\t'  << MAXSIGNATURA << endl;
     cout << "maximo similitudes" << '\t' << ranghash << endl;
    
    cout << endl;
    cout << "Por Jaccard: " << endl;
    for (int i = 0; i<NUM_DOCS;++i) {
	cout << "Document " << nomdocs[i] << '\t';
	float jac_doc;
	if (i == 0) jac_doc = 1;
	else jac_doc = jacobianas[i-1];
	cout << "shingles totales " << numsingles[i] << " jac " << jac_doc << endl;
	//for(int j = i; j<NUM_DOCS; ++j) {
	//  if ()
	//}
    }
	cout << "time:" << '\t' << t.elapsed()<< endl;
}
