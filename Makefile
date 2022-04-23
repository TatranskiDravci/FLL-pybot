PLATFORM = GOOS=linux GOARCH=arm GOARM=5

run1: run1.go sensing.go env.go shifter.go exten.go move.go base.go pid.go modules.go
	$(PLATFORM) go build -o build/run1 $^

run2: run2.go sensing.go env.go shifter.go exten.go move.go base.go pid.go modules.go
	$(PLATFORM) go build -o build/run2 $^

calib: calibrate.go sensing.go env.go exten.go
	$(PLATFORM) go build -o build/calibrate $^

vpath %.go src

clean:
	rm build/*

init:
	mkdir build
