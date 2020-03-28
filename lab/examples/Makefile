all clean:
	@for subdir in helloworld thread framebuffer  ebbchar;\
	do\
		#echo $$subdir;\
		if test -d $$subdir;\
		then\
		echo making $@ in $$subdir;\
		(cd $$subdir && make $@) || exit 1;\
		fi;\
	done

