build: bundle

bundle:
	rm -rf node_modules && npm install

test: bundle
	vows --spec
