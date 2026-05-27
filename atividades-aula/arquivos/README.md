# Sistema de Vendas e Estoque em C

Este é um sistema de gerenciamento de vendas e controle de estoque baseado em arquivos binários, desenvolvido em linguagem C. 

## 👥 Desenvolvedores

Este projeto foi desenvolvido em dupla por:
* **Lucas Vinícius da Silva(00000860598)**
* **Gilberto Alves da Silva Junior(00000860506)**

---

## 🚀 Funcionalidades

O sistema opera via terminal de comando através de um menu interativo com as seguintes opções:

### Gerenciamento de Produtos
* **Cadastrar produto:** Registra ID (único), Nome, Preço e Estoque.
* **Listar produtos:** Exibe todos os produtos salvos no arquivo `produtos.dat`.
* **Buscar produto:** Localiza um item específico a partir do ID.
* **Atualizar produto:** Permite alterar as informações de um produto existente.
* **Remover produto:** Exclui permanentemente um produto do estoque.

### Gerenciamento de Vendas
* **Cadastrar venda:** Registra ID da venda, Nome do cliente e uma lista de até 10 produtos associados, calculando o valor total automaticamente.
* **Listar vendas:** Exibe o histórico de vendas salvas em `vendas.dat` com os nomes dos produtos relacionados.
* **Buscar venda:** Localiza uma venda específica pelo ID.
* **Atualizar venda:** Permite atualizar o nome do cliente de uma venda.
* **Remover venda:** Exclui permanentemente o registro de uma venda.