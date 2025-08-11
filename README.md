![](Aspose.Words.764494f5-e01c-4ec7-8c71-247efce4dff8.001.png)

**# Sistema de Gerenciamento da Livraria** 

Trata-se  de  um  sistema  para  o  gerenciamento  de  uma  livraria,  permitindo  o cadastro e remoção de livros. O sistema foi implementado na linguagem C e utiliza arquivos binários para armazenar os dados de forma persistente, garantindo que as informações não sejam perdidas ao fechar o programa. O algoritmo foi implementado com a estrutura de Árvore Binária de Busca. 

**## Funcionalidades Implementadas** 

O sistema possui 9 (nove) opções, sendo: 

1. **Cadastrar livro:** 
1. Esta opção permite adicionar um novo livro ao acervo da livraria. 
1. **Como usar:** você precisará fornecer as respectivas credenciais do livro, como o código, título da obra, nome do autor, editora, o número da edição, ano de publicação, quantidade de exemplares disponíveis e o preço legítimo da obra. Caso a inserção de um livro com o mesmo código ou um custo de livro incorreto, mensagens de *“não é possivel registrar livros com código duplicado”* e *“custo de obra inválida”* serão exibidas, respectivamente.  
2. **Informações de um respectivo livro:** 
1. Esta  opção  permite  consultar  as  informações  detalhadas  de  um  livro registrado no sistema de acordo com seu código cadastrado. 
1. **Como usar:** você precisará fornecer o código do livro exatamente como foi registrado no sistema no momento de seu cadastro, sem zeros à esquerda. Caso o livro existir, o sistema exibirá as informações. Caso contrário, uma mensagem de *‘‘não encontrado’’* será exibida. 
3. **Listar todos os livros cadastrados:** 
1. Exibe uma lista formatada com as informações principais de todos os livros que estão no sistema, em ordem crescente, com código, título da obra, nome do autor e quantidade de exemplares disponíveis. Caso não possuir nenhum livro  no  sistema,  uma  mensagem  de  *“árvore  vazia,  nenhum  livro  foi cadastrado”* será exibida. 
1. **Como usar:** apenas selecione a opção no menu para visualizar a tabela completa. 
4. **Calcular total de livros cadastrados:** 
1. Exibe na tela a quantidade total de livros cadastrados no sistema. Caso nenhum livro for cadastrado, aparecerá um resultante equivalente à *“0”*. 
1. **Como usar:** apenas selecione a opção no menu para visualizar a quantidade total. 
5. **Remover livro:** 
1. Esta opção permite a remoção de um respectivo livro. 
1. **Como usar:** você precisará informar o código do livro correspondente. Caso 

   o livro com o código não exista, uma mensagem *“livro com código não foi encontrado para remoção”*. Se nenhum livro estiver cadastrado no sistema, alertará que *“não há livros para remover, árvore vazia”.* 

6. **Carregar arquivo em Lote:** 
1. Esta funcionalidade realiza inclusões em lote, carregando informações de livros que estão armazenados dentro de um arquivo de texto *.txt*. O sistema lê os dados deste arquivo e os insere diretamente no arquivo binário de cadastro do sistema, ideal para popular o banco de forma rápida. Ele também realiza a contagem da quantidade de registros processados e os exibe na tela. Se houver um livro para cadastro com o mesmo código de um livro que já foi cadastrado no sistema, uma mensagem de aviso  *“não foi possivel cadastrar o livro”* será exibido.* 
1. **Como usar:** você precisará informar o nome do arquivo texto exatamente como está registrado, com letras maiúsculas, minúsculas ou *underline* (\_), se existir, para o sistema puder acessá-lo. **Obs:** O nome do arquivo texto deve ter, no máximo, 255 caracteres e não é necessário inserir a extensão *“.txt”*. O arquivo precisa** estar **OBRIGATORIAMENTE** no diretório *“example/”* para o funcionamento correto.***   
7. **Listar todos os registros livres:** 
1. Esta opção permite a visualização de todas as posições de registros livres que há na árvore. As posições são atualizadas a cada remoção de um livro do sistema e decrementada a cada novo cadastro de livro. Caso não houver nenhuma posição livre disponível, uma *mensagem “não há registros livres no sistema”* será exibida.* 
1. **Como usar:** apenas selecione a opção do menu para verificar a sequência.*** 
8. **Imprimir árvore por níveis:** 
1. Esta funcionalidade faz a impressão da árvore do arquivo binário do sistema, exibindo, respectivamente, os nós com os códigos dos livros correspondentes em suas alturas. Caso o sistema não possuir nenhum cadastro de livro a árvore estará vazia, portanto, uma mensagem de *“árvore vazia”* será exibida.* 
2. **Como usar:** apenas selecione a opção do menu para visualizar todos os níveis.* 

**0.  Sair:** 

1. Sai do sistema e salva os dados do programa. 
1. **Como usar:** apenas selecione a opção do menu. 
