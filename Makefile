build: bundle

bundle:
	npm install

test: bundle
	vows --spec
