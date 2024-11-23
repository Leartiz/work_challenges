build_image:
	cd server && \
	docker build . -t wc1_server

run_server: build_image \
	docker run wc1_server