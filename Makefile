.PHONY: clean run init

all: clean run
init:
	pip install -r requirements.txt
run:
	python main.py
clean:
	rm -rf *.png
activate:
    source venv/bin/activate
