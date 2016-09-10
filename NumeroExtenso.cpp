/*
 * NumeroExtenso.cpp
 * 
 * Copyright 2016 Rafael Andrade <rafaelsandrade@gmail.com>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 10/09/2016
 */

#include <cstdio>
#include <cstring>


//// Função que recebe um número inteiro e retorna um texto do número por extenso
void numExtenso(const int num, char *extenso)
{
    char numero[15] = "";
    
    const char unid[19][10] = {"um", "dois", "três", "quatro", "cinco", "seis", 
                               "sete", "oito", "nove", "dez", "onze", "doze", "treze", 
                               "quatorze", "quinze", "dezesseis", "dezessete", 
                               "dezoito", "dezenove"};
                        
    const char dezena[8][10] = {"vinte", "trinta", "quarenta", "cinquenta", "sessenta", 
                                 "setenta", "oitenta", "noventa"};
    
    const char centena[9][13] = {"cento", "duzentos", "trezentos", "quatrocentos", "quinhentos",
                                  "seiscentos", "setecentos", "oitocentos", "novecentos"};

    
    // Converte de inteiro para string
    sprintf(numero, "%d", num);
    
    // Se for zero ou string vazia retorna 'zero'
    if (!strcmp(numero, "0") || numero[0] == '\0')
    {
        strcpy(extenso, "zero");
        return;
    }
    
    // Limpa a string 'extenso'
    extenso[0] = '\0';
    
    // Armazena o número de dígitos
    int n_digito = strlen(numero);
    
    for (int i = 0; i < n_digito; i++)
    {
        // Leitura das centenas
        if (((n_digito - 1 - i) % 3 == 2) && (numero[i] != '0'))
        {
            // Se 'extenso' não está vazio, acrescenta o conectivo 'e'
            if (extenso[0] != '\0')
            {
                strcat(extenso, " e ");
            }
            
            // Se for 100 escreve 'cem'
            if (numero[i] == '1' && numero[i + 1] == '0' && numero[i + 2] == '0')
            {
                strcat(extenso, "cem");
                continue;
            }
            else
            {   
                // Escreve o nome da centena
                strcat(extenso, centena[(numero[i] - 48) - 1]);
            }           
            
        }
        
        // Leitura das dezenas entre 20 e 99
        if ((n_digito - 1 - i) % 3 == 1 && numero[i] != '0')
        {
            // Se dezena for entre 10 e 19, passa para o próximo IF
            if (numero[i] == '1')
            {
                continue;
            }
            else
            {
                // Se 'extenso' não está vazio, acrescenta o conectivo 'e'
                if (extenso[0] != '\0')
                {
                    strcat(extenso, " e ");
                }
                
                // Escreve o nome da dezena
                strcat(extenso, dezena[numero[i] - 50]);
                
                continue;
            }
        }
        
        // Leitura da unidades e das dezenas entre 10 e 19
        if ((n_digito - 1 - i) % 3 == 0)
        {
            // Se for dezena entre 10 e 19
            if (n_digito > 1 && numero[i - 1] == '1')
            {
                // Acrescenta o conectivo 'e'
                if (extenso[0] != '\0')
                {
                    strcat(extenso, " e ");
                }
                
                // Escreve o nome da dezena
                strcat(extenso, unid[(numero[i] - 48) + 9]);
            }
            else 
            {
                // Se for unidade
                if (numero[i] != '0')
                {
                    // Acrescenta o conectivo 'e'
                    if (extenso[0] != '\0')
                    {
                        strcat(extenso, " e ");
                    }
                    
                    // Escreve o nome da unidade
                    strcat(extenso, unid[numero[i] - 49]);
                }
            }
        }
        
        // Acrescenta o texto 'mil'
        if ((n_digito - i) == 4)
        {
            // Verifica se existe algum milhar
            for (int j = i; (j >= 0) && (i - j < 3); j--)
            {
                if (numero[j] != '0')
                {
                    strcat(extenso, " mil");
                    break;
                }                
            }
        }
        
         // Acrescenta o texto 'milhão' ou 'milhões'
        if ((n_digito - i) == 7)
        {   
            // Verifica se o número é do formato 001.XXX.XXX
            if ((numero[i] == '1') && (n_digito == 7 || (n_digito == 8 && numero[i - 1] == '0') ||
                (n_digito == 9 && numero[i - 1] == '0' && numero[i - 2] == '0')))
            {
                strcat(extenso, " milhão");
            }
            else
            {
                // Verifica se existe algum milhão
                for (int j = i; (j >= 0) && (i - j < 3); j--)
                {
                    if (numero[j] != '0')
                    {
                        strcat(extenso, " milhões");
                        break;
                    }                
                }
            }
        }
    }
}


int main(int argc, char** argv)
{
    char str[100];
    
    int i = 123456789;

    numExtenso(i, str);

    printf("%d - \"%s\"\n", i, str);
    
    return 0;
}
