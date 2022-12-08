build mvm: mvmroulette.cc
	g++ *.cc -g -o mvm

run: mvm
	./mvm

clean:
	-rm -rf mvm