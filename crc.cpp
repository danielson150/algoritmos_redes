/*
Verificação cíclica de redundância (CRC):
*/

#include<iostream>

using namespace std;

string xorfunction( string encoded , string gx)							//Operação XOR bit a bit
{
	int gxlen = gx.length();

	for ( int i = 0 ; i <= (encoded.length() - gxlen) ; )			// executando operação xor bit a bit
	{																// " 0 xor 0 = 0"     " 1 xor 1 = 0 "
		for( int j=0 ; j < gxlen ; j++)							// " 0 xor 1 = 1 "    " 1 xor 0 = 1"
		{
			encoded[i+j] = encoded[i+j] == gx[j] ? '0' : '1' ;			//se bit codificado e bit crc forem iguais, substitua-o por zero
		}
	for( ; i< encoded.length() && encoded[i] != '1' ; i++) ;

	}

	return encoded;
}

int main()
{
    /*M(x): Palavra inicial
      G(x): Polimônio Gerador
      R: Grau de G(x)
      */
	string mx , gx , encoded = "";
	cout<<endl<<"-----------Remetente --------------"<<endl;
	cout<<"Inserir bits de dados: "<<endl;
	cin>>mx;														//bits de dados a serem transmitidos

	cout<<"Digite o polimônio gerador: "<<endl;
	cin>>gx;														//crc - polinômio do gerador

	encoded += mx;			//bits codificados são inicializados em bits de dados

	int mxlen = mx.length(); //Guardar o tamanho da string de M(x)
	int gxlen = gx.length(); //Guardar o tamanho da string de G(x)

	for(int i=1 ; i <= (gxlen - 1) ; i++)
		encoded += '0';			//anexando comprimento de (gerador polinomial -1) número de zeros aos bits codificados

	encoded = xorfunction(encoded , gx);	//executando xor bit a bit para obter

	cout<<"A soma de verificação gerada é: ";
	cout<<encoded.substr(encoded.length() - gxlen + 1)<<endl<<endl;   //bits de dados + bit de soma de verificação é o que será enviado para o receptor
	cout<<"Mensagem a ser transmitida: ";
	cout<<mx + encoded.substr(encoded.length() - gxlen + 1);    	//esta é a mensagem que será enviada ao receptor




	cout<<endl<<"---------------Receptor-----------------"<<endl;


    	string msg;
	cout<<"Digite a mensagem recebida: "<<endl;             //O receptor entra na mensagem recebida
	cin>>msg;

	msg = xorfunction( msg , gx);

	for( char i : msg.substr(msg.length() - gxlen + 1))	//depois de executar xor, se os últimos bits forem zero, não haverá erro na transmissão
		if( i != '0' )
			{
				cout<<"Erro na transmissão!!! "<<endl;	//se bits não forem zero; ERRO NA TRANSMISSÃO
				return 0;
			}

	cout<<"Nenhum erro!"<<endl;												//bit a bit xor é realizado entre os bits recebidos e os bits crc do gerador
	return 0;
}
