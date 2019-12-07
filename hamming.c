#include<stdio.h>
#include<math.h>
#define MAX 30

int main(){
	int i, m, b, c[MAX], d, r = 0, d1, err[10] = {0}, esc_parity;

	printf("Digite a quantidade de bits de dados que você deseja inserir:\n");
	scanf("%d", &m);


	printf("Qual a paridade? 1-IMPAR ou 0-PAR:\n");
	scanf("%d", &esc_parity);

	/*2 r ≥ m + r + 1 (Fórmula)
	>Onde r é o número de bits redudantes
	>m é número de bits de dados
	*/
	while (m + r + 1 > pow(2, r))
	{
		r++;
	}

	printf("Número de bits de dados redundantes a serem adicionados: %d\n", r);
	printf("Total de Bits(dados+ redudante): %d", m+r);

	printf("\nInsira os bits de dados: (UM A UM)\n");
	for(i=1;i<=m; i++){
		scanf("%d", &c[i]);
	}

	printf("Bits de dados inseridos:\n");
	for(i=1;i<=m;i++){
		printf("%d", c[i]);
	}

	int data[m + r], res[m+r];
    d = 0;
    d1 = 1;
	for (i = 1; i <= m + r; i++)
    {
      if ((i) == pow (2, d))
        {
        data[i] = 0;
        d++;
        }
      else
        {
        data[i] = c[d1];
        d1++;
        }
    }

	/*printf("\nOs bits de dados são codificados com bits de paridade(0):\n");
	for(i=1; i<=m+r;i++){
		printf("%d", data[i]);
	}*/

	d1 = 0;
    int min, max = 0, parity, s, j;

    /*Parity Bit Calculation */
    for (i = 1; i <= m + r; i = pow (2, d1))
    {
          d1++;
          parity = 0;
          j = i;
          s = i;
          min = 1;
          max = i;
          for (j; j <= m + r;)
          {
                 for (s = j; max >= min && s <= m + r; ++min, ++s)
                 {
                        if (data[s] == 1)
                        parity++;
                 }
                  j = s + i;
                  min = 1;
          }

      if(esc_parity == 0){
      if (parity % 2 == 0) // Paridade PAR
      {
            data[i] = 0;
      }
      else
      {
            data[i] = 1;
      }
      }

      if(esc_parity == 1){
      if (parity % 2 == 0) // Paridade IMPAR
      {
            data[i] = 1;
      }
      else
      {
            data[i] = 0;
      }
      }

    }

    printf("\nA sequencia final transmitida para paridade selecionada é:\n");
    for(i=1; i<=m+r ; i++){
        printf("%d", data[i]);
    }

    printf("\nDigite a sequencia recebida. Insira os bits de UM A UM:\n");
    for(i=1; i<=m+r; i++){
        scanf("%d", &res[i]);
    }

    d1=0; max=0; int ec=0;

    for (i = 1; i <= m + r; i = pow (2, d1))
    {
      d1++;
      parity = 0;
      j = i;
      s = i;
      min = 1;
      max = i;
      for (j; j <= m + r;)
    {
        for (s = j; max >= min && s <= m + r; ++min, ++s)
        {
        if (res[s] == 1)
            parity++;
        }
        j = s + i;
        min = 1;
    }

    if(esc_parity==0){
     if (parity % 2 == 0) // Paridade PAR
    {
    err[ec]=0;
    ec++;
    }
      else
    {
    err[ec]=1;
    ec++;
    }
    }

    if(esc_parity==1){
     if (parity % 2 == 0) // Paridade IMPAR
    {
    err[ec]=1;
    ec++;
    }
      else
    {
    err[ec]=0;
    ec++;
    }
    }

    }

    int flag = 1;
    for(i =r-1;i>=0;i--)
    {
        if(err[i]==1)
        {
            flag =0;
            break;
        }
    }


    if(flag==0)
    {
        int pos=0;
    printf("Erro detectado em:\n");
    for(i =r-1;i>=0;i--)
    {
        printf("%d", err[i]);

        if(err[i]==1)
            pos+=pow(2,i);
    }
        printf("\nPosição de erro: %d", pos);
        res[pos]=!res[pos];
        printf("\nApós correção: ");
        for(i =1;i<=m+r;i++)
          printf("%d", res[i]);
    }
    else
       printf("Nenhum erro foi detectado");


	return 0;
}
