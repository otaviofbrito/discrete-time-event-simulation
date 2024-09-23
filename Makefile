.PHONY: all c_project python_script clean setup

# Alvo principal que chama os dois alvos
all: env c_project python_script

env: 
	@if [ ! -d ".env" ]; then \
		echo "[WARNING]: O ambiente virtual não foi criado. Execute 'make build' primeiro!"; \
		exit 1; \
	fi
	
# Alvo para rodar o Makefile dentro de c_project
c_project:
	$(MAKE) -C c_project

# Alvo para rodar o script Python
python_script:
	. .env/bin/activate; python3 python_project/main.py; deactivate


# Alvo para executar o clean do Makefile dentro de c_project
clean:
	$(MAKE) -C c_project clean
	@if [ -f report.html ]; then rm report.html; fi
	@echo "[OK]: Ambiente limpo!"

# Alvo para configurar o ambiente Python
build:
	@echo "[INFO]: Criando ambiente virtual..."
	python3 -m venv .env
	@echo "[INFO]: Instalando dependências no ambiente virtual ..."
	. .env/bin/activate; pip install -r requirements.txt; deactivate
	@echo "[OK]: Ambiente virtual criado!"

