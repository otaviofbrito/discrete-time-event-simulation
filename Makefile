.PHONY: all c_project python_script clean setup

# Alvo principal que chama os dois alvos
all: c_project python_script

# Alvo para rodar o Makefile dentro de c_project
c_project:
	$(MAKE) -C c_project

# Alvo para rodar o script Python
python_script:
	python3 python_project/main.py

# Alvo para executar o clean do Makefile dentro de c_project
clean:
	$(MAKE) -C c_project clean
	@if [ -f report.html ]; then rm report.html; fi

# Alvo para configurar o ambiente Python
build:
	@echo "Criando ambiente virtual..."
	python3 -m venv .env
	@echo "Ativando ambiente virtual..."
	. .env/bin/activate && \
	echo "Instalando dependências do requirements.txt..." && \
	pip install -r requirements.txt && \
	echo "Criando arquivo .env..." && \
	echo ".env criado com sucesso!"

