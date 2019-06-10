# PetHero

O PetHero é um sistema que liga pessoas que não conseguem tomar mais conta de seus animais de estimação com pessoas que estão interessadas em adotar um pet. 

## Integrantes

- Henrique Faria de Paiva Fagundes
- João Pedro Bahia Zica

## Como compilar e executar o código

Para compilar o projeto, basta rodar o comando `make build` que o g++ será invocado com todos os arquivos e flags necessários.

Para executar o programa, basta rodar `make run`! Após isso, você pode acessar o site através do seu [localhost](localhost:8080) na porta 8080.

## Como usar

Ao acessar o link, é necessário que o visitante se cadastre na plataforma ou faça seu login.
Após esses passos, as opções de animais são exibidas e ele pode indicar seu interesse por eles ou não.

Ao indicar o interesse, o usuário dono do animal poderá visualizar as informações do interessado e contatá-lo da maneira que preferir para realizarem algum tipo de acordo.

O usuário também pode cadastrar animais que possui para que sejam exibidos aos outros usuários da plataforma.

### Dados técnicos

O sistema utiliza um banco de dados SQlite 3 e roda sobre um servidor baseado em C++.

### User Stories

    - Como um usuário do sistema eu quero poder visualizar os animais que
    estão disponíveis para adoção para que eu possa tomar uma decisão.

    - Como um usuário que não quer ter mais um animal de estimação em casa
    eu quero poder cadastrar meu pet para conseguir repassá-lo para outra pessoa interessada

    - Como um usuário interessado em animais pequenos eu quero poder filtar
    os animais exibidos de acordo com certas caracteríscas para facilitar minha busca.
    
    - Como um usuário do sistema que tomou uma decisão sobre qual pet eu desejo adotar eu quero 
    poder contatar o dono de tal pet para que eu possa adotá-lo
    
    - Como um usuário do sistema que recentemente mudou de endereço eu quero poder
    alterar meus dados cadastrais para que minhas informações fiquem atualizadas
    
    - Como um indivíduo interessado em utilizar a plataforma eu quero poder
    cadastrar meus dados pessoais para que eu possa utilizar o sistema


## DSL

  - {{}} -> Utilizado para representar um atributo
  - [[]] -> Utilizado para representar a inserção em loop do mesmo partial