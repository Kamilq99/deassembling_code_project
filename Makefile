CC = gcc
CFLAGS = -Wall -O2 -mwindows -m32
LDFLAGS = -lgdi32

all: LicenseVerifier.exe VerifyKey/verify_key.dll

LicenseVerifier.exe: GUI/graphical_user_interface.o VerifyKey/verify_key.dll
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

GUI/graphical_user_interface.o: GUI/graphical_user_interface.c
	$(CC) $(CFLAGS) -c $< -o $@

VerifyKey/verify_key.dll: VerifyKey/verify_key.c
	$(CC) $(CFLAGS) -shared -o $@ $<
	copy $@ .

clean:
	del GUI\*.o VerifyKey\*.o LicenseVerifier.exe VerifyKey\*.dll