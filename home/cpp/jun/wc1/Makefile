build_image:
	cd server && \
	docker build . -t wc1_server

run_server: build_image \
	docker run -d -p 24445:24444 wc1_server