#include <iostream>
#include <string>

using namespace std;


// ==========================================
// STRUCT DO PACIENTE
// ==========================================

struct Paciente
{
    string nome;
    int idade;
    string cpf;
    int prioridade;
};



// ==========================================
// NO DA LISTA ENCADEADA
// ==========================================

struct No
{
    Paciente dados;
    No *proximo;
};



// ==========================================
// LISTA
// ==========================================

struct Lista
{
    No *inicio;
};



// ==========================================
// INICIALIZAR LISTA
// ==========================================

void inicializar(Lista &lista)
{
    lista.inicio = NULL;
}



// ==========================================
// VALIDAR NOME
// ==========================================

bool nomeValido(string nome)
{

    for(int i = 0; i < nome.length(); i++)
    {

        if(nome[i] >= '0' && nome[i] <= '9')
        {
            return false;
        }

    }


    return true;
}



// ==========================================
// FORMATAR CPF
// 12345678900
// vira
// 123.456.789-00
// ==========================================

string formatarCPF(string cpf)
{

    string novoCPF;


    novoCPF =
    cpf.substr(0,3) + "." +
    cpf.substr(3,3) + "." +
    cpf.substr(6,3) + "-" +
    cpf.substr(9,2);


    return novoCPF;
}



// ==========================================
// VALIDAR CPF
// ==========================================

bool cpfValido(string cpf)
{

    if(cpf.length() != 11)
    {
        return false;
    }


    for(int i = 0; i < cpf.length(); i++)
    {

        if(cpf[i] < '0' || cpf[i] > '9')
        {
            return false;
        }

    }


    return true;
}



// ==========================================
// VERIFICAR CPF REPETIDO
// ==========================================

bool cpfExiste(Lista lista, string cpf)
{

    No *aux = lista.inicio;


    while(aux != NULL)
    {

        if(aux->dados.cpf == cpf)
        {
            return true;
        }


        aux = aux->proximo;

    }


    return false;
}



// ==========================================
// INSERÇÃO NA LISTA
// ==========================================

void inserir(Lista &lista, Paciente p)
{

    No *novo = new No;


    novo->dados = p;

    novo->proximo = NULL;



    // lista vazia

    if(lista.inicio == NULL)
    {
        lista.inicio = novo;
    }



    // prioridade entra na frente

    else if(p.prioridade == 1)
    {

        novo->proximo = lista.inicio;

        lista.inicio = novo;

    }



    // normal entra no final

    else
    {

        No *aux = lista.inicio;


        while(aux->proximo != NULL)
        {
            aux = aux->proximo;
        }


        aux->proximo = novo;

    }

}

//Foi utilizada uma lista encadeada porque a quantidade de pacientes pode variar durante a execução do programa.
// Diferente de um vetor, a lista encadeada permite criar e remover elementos dinamicamente utilizando ponteiros,
// sem precisar definir um tamanho fixo de memória

// ==========================================
// REMOVER PACIENTE
// ==========================================

void remover(Lista &lista)
{

    if(lista.inicio == NULL)
    {
        cout << "\nFila vazia!\n";
        return;
    }



    No *aux = lista.inicio;


    lista.inicio = lista.inicio->proximo;



    cout << "\nPaciente atendido:\n";

    cout << "Nome: "
         << aux->dados.nome << endl;


    cout << "Idade: "
         << aux->dados.idade << endl;


    cout << "CPF: "
         << aux->dados.cpf << endl;



    if(aux->dados.prioridade == 1)
    {
        cout << "Prioridade: Urgencia\n";
    }
    else
    {
        cout << "Prioridade: Normal\n";
    }



    delete aux;

}

//O ponteiro principal está dentro do nó, apontando para o próximo elemento da lista.
//Também utilizo ponteiros auxiliares para percorrer a lista, encontrar elementos e realizar inserções e remoções.

// ==========================================
// MOSTRAR FILA
// ==========================================

void mostrar(Lista lista)
{

    No *aux = lista.inicio;


    if(aux == NULL)
    {
        cout << "\nFila vazia!\n";
        return;
    }



    cout << "\n========= FILA DE PACIENTES =========\n";



    while(aux != NULL)
    {

        cout << "\nNome: "
             << aux->dados.nome;


        cout << "\nIdade: "
             << aux->dados.idade;


        cout << "\nCPF: "
             << aux->dados.cpf;



        if(aux->dados.prioridade == 1)
        {
            cout << "\nPrioridade: Urgencia";
        }
        else
        {
            cout << "\nPrioridade: Normal";
        }


        cout << "\n-----------------------------------";


        aux = aux->proximo;

    }

}

//Os principais ponteiros são o ponteiro proximo, que conecta os nós da lista,
//e os ponteiros auxiliares usados nas funções de busca, inserção e remoção, como o aux.
// Também existe o ponteiro criado dinamicamente no momento da inserção usando new


// ==========================================
// PROGRAMA PRINCIPAL
// ==========================================

int main()
{

    Lista fila;


    inicializar(fila);



    int opcao;



    do
    {

        cout << "\n\n========== CLINICA MEDICA ==========";
        cout << "\n1 - Cadastrar paciente";
        cout << "\n2 - Atender paciente";
        cout << "\n3 - Mostrar fila";
        cout << "\n0 - Sair";


        cout << "\nEscolha: ";

        cin >> opcao;



        switch(opcao)
        {


        case 1:
        {

            Paciente p;


            cin.ignore();



            // NOME

            do
            {

                cout << "\nNome: ";

                getline(cin,p.nome);



                if(!nomeValido(p.nome))
                {
                    cout << "Nome invalido! Nao use numeros.\n";
                }


            }while(!nomeValido(p.nome));


//A prioridade é controlada pela variável prioridade, onde o valor 1 representa urgência e o valor 0 representa atendimento normal.
// Quando um paciente urgente é cadastrado, ele é colocado no começo da lista.
//Já pacientes normais são inseridos no final.


            // IDADE

            while(true)
            {

                cout << "Idade: ";

                cin >> p.idade;



                if(cin.fail())
                {

                    cin.clear();

                    cin.ignore(1000,'\n');


                    cout << "Digite apenas numeros!\n";

                }
                else
                {
                    break;
                }

            }



            // CPF

            do
            {

                cout << "CPF (11 numeros): ";

                cin >> p.cpf;



                if(!cpfValido(p.cpf))
                {
                    cout << "CPF invalido!\n";
                }
                else if(cpfExiste(fila, formatarCPF(p.cpf)))
                {
                    cout << "CPF ja cadastrado!\n";
                }


            }while(!cpfValido(p.cpf) ||
                   cpfExiste(fila, formatarCPF(p.cpf)));



            p.cpf = formatarCPF(p.cpf);





            // PRIORIDADE

            do
            {

                cout << "\nPrioridade:";
                cout << "\n1 - Urgencia";
                cout << "\n0 - Normal";


                cout << "\nEscolha: ";

                cin >> p.prioridade;



                if(p.prioridade != 0 &&
                   p.prioridade != 1)
                {
                    cout << "Digite somente 0 ou 1!\n";
                }



            }while(p.prioridade != 0 &&
                   p.prioridade != 1);




            inserir(fila,p);



            cout << "\nPaciente cadastrado com sucesso!\n";


            break;

        }



        case 2:

            remover(fila);

            break;



        case 3:

            mostrar(fila);

            break;



        case 0:

            cout << "\nSistema encerrado.";

            break;



        default:

            cout << "\nOpcao invalida!";

        }



    }while(opcao != 0);



    return 0;
}
