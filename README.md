# SoalShiftSISOP20_modul2_C01

### KELOMPOK        : C1
ANGGOTA         :

* Vieri Fath Ayuba     (05111840000153)
* Himawan Wijaya       (05111640000133)


### Jawaban Soal Shift Modul 3
### NO 3
Buatlah sebuah program dari C untuk mengkategorikan file. Program ini akan
memindahkan file sesuai ekstensinya (tidak case sensitive. JPG dan jpg adalah
sama) ke dalam folder sesuai ekstensinya yang folder hasilnya terdapat di working
directory ketika program kategori tersebut dijalankan.
● Semisal program dijalankan:
# File kategori terletak di /home/izone/kategori
$ ./kategori -f path/to/file1.jpg path/to/file2.c path/to/file3.zip
#Hasilnya adalah sebagai berikut
/home/izone
|-jpg
|--file1.jpg
|-c
|--file2.c
|-zip
|--file3.zi
● Pada opsi -f tersebut, user bisa menambahkan argumen file yang bisa
dikategorikan sebanyak yang user inginkan seperti contoh di atas.
● Pada program kategori tersebut, folder jpg,c,zip tidak dibuat secara manual,
melainkan melalui program c. Semisal ada file yang tidak memiliki ekstensi,
maka dia akan disimpan dalam folder “Unknown”.
● Program kategori ini juga menerima perintah (*) seperti di bawah;
$ ./kategori \*
● Artinya mengkategori seluruh file yang ada di working directory ketika
menjalankan program C tersebut.
● Selain hal itu program C ini juga menerima opsi -d untuk melakukan kategori
pada suatu directory. Untuk opsi -d ini, user hanya bisa menginput 1 directory
saja, tidak seperti file yang bebas menginput file sebanyak mungkin.
$ ./kategori -d /path/to/directory/
● Hasilnya perintah di atas adalah mengkategorikan file di /path/to/directory dan
hasilnya akan disimpan di working directory di mana program C tersebut
berjalan (hasil kategori filenya bukan di /path/to/directory).
● Program ini tidak rekursif. Semisal di directory yang mau dikategorikan, atau
menggunakan (*) terdapat folder yang berisi file, maka file dalam folder
tersebut tidak dihiraukan, cukup file pada 1 level saja.
● Setiap 1 file yang dikategorikan dioperasikan oleh 1 thread agar bisa berjalan
secara paralel sehingga proses kategori bisa berjalan lebih cepat. Dilarang
juga menggunakan fork-exec dan system.
● Silahkan download soal3.zip sebagai percobaan. Namun silahkan
dicoba-coba sendiri untuk kemungkinan test case lainnya yang mungkin
belum ada di soal3.zip.

#### Fungsi getExt digunakan untuk mendapatkan string setelah "." dan fungsi getDir digunakan untuk mendapatkan string setelah "/" 


```
char *getExt (char fspec[]) {
    char *e = strrchr (fspec, '.');
    if (e == NULL)
        e = ""; 
    return e;
}
char *getDir (char fspec[]) {
    char *e = strrchr (fspec, '/');
    if (e == NULL)
        e = ""; 
    return e;
}

```

#### Program ini tidak case sensitive, jadi huruf kapital diganti huruf kecil biar sama

```
void lower_string(char s[]) {
   int c = 0;
   
   while (s[c] != '\0') {
      if (s[c] >= 'A' && s[c] <= 'Z') {
         s[c] = s[c] + 32;
      }
      c++;
   }
}
```

#### Ekstensi dari nama file tersebut untuk membuat nama folder "strtok(getExt((in)),".")"   
#### Jika tidak ekstensi maka akan membuat folder "Unknown" 
```
void* categoryf(void *arg){
    char nf[100];
    char na[100];
    strcpy(na,strtok(getExt((in)),"."));
    lower_string(na);
    memset(nf, '\0', sizeof(nf));
    if(strlen(getExt(in)) != 0){
     if (stat(na, &st) == -1)
     {
        mkdir(na,0777);
     }
     sprintf(nf,"%s/%s",  na, strtok(getDir(in),"/") );
     rename(in, nf);
     }
     else{
     if (stat("Unknown)", &st) == -1)
     {    
        mkdir("Unknown",0777);
     }
     sprintf(nf,"Unknown/%s",strtok(getDir(in),"/"));
     rename(in, nf);
     }
}
```
#### Mmbuka direktori file dan memindahkan kedalam folder sesuai exstensinya, dan jika tidak punya extensi maka akan dipindahkan ke folder "Unknown".

```
void* categorystar(void *arg){
    char nama[100];
    struct dirent *de;
    DIR *dr = opendir(".");
    while ((de = readdir(dr)) != NULL){ 
       if (de->d_type == DT_REG)
       {    
         if(strlen(getExt(de->d_name)) != 0){
              char na[100];
              strcpy(na,strtok(getExt((de->d_name)),"."));
              lower_string(na);
              if (stat(na, &st) == -1)
              {
                 mkdir(na,0777);
              }
              sprintf(nama,"%s/%s",na,de->d_name);
              rename(de->d_name , nama);
           
        }
       else{
         if (stat("Unknown)", &st) == -1)
         {    
             mkdir("Unknown",0777);
         }
         sprintf(nama,"Unknown/%s",de->d_name);
         rename(de->d_name, nama);
       }}
    }
    closedir(dr);
}
```

#### Pada opsi -f tersebut, user bisa menambahkan argumen file yang bisa dikategorikan sebanyak yang user inginkan seperti contoh di atas.

```
    if(strcmp(argv[1],"-f")==0){
        for (int i = 2; i < argc; i++) {
           strcpy(in,argv[i]);
           int* p;
           pthread_create(&threads[i-1], NULL, categoryf, (void*)(p));
           pthread_join(threads[i-1], NULL);
           printf("%s\n",input(in));
        }
    }
```



#### Untuk opsi -d ini, user hanya bisa menginput 1 directory saja, tidak seperti file yang bebas menginput file sebanyak mungkin.


```
    else if(strcmp(argv[1],"-d") == 0){
        struct dirent *de;
        DIR *dr = opendir(argv[2]);
        while ((de = readdir(dr)) != NULL){ 
        if (de->d_type == DT_REG)
        {
          a++;
        }
        }
        printf("%d\n",a);
        closedir(dr);
        strcpy(in,argv[2]);
        for(int b=0;b<a;b++){
           int* p;
           pthread_create(&threads[b], NULL, categoryd, (void*)(p));
           pthread_join(threads[b], NULL);
        }

    }
}
```















### NO 4
4. Norland adalah seorang penjelajah terkenal. Pada suatu malam Norland menyusuri
jalan setapak menuju ke sebuah gua dan mendapati tiga pilar yang pada setiap
pilarnya ada sebuah batu berkilau yang tertancap. Batu itu berkilau di kegelapan dan
setiap batunya memiliki warna yang berbeda.
Norland mendapati ada sebuah teka-teki yang tertulis di setiap pilar. Untuk dapat
mengambil batu mulia di suatu pilar, Ia harus memecahkan teka-teki yang ada di
pilar tersebut. Norland menghampiri setiap pilar secara bergantian.
- Batu mulia pertama . Emerald. Batu mulia yang berwarna hijau mengkilat. Pada
batu itu Ia menemukan sebuah kalimat petunjuk. Ada sebuah teka-teki yang berisi:
1. Buatlah program C dengan nama " 4a.c ", yang berisi program untuk
melakukan perkalian matriks. Ukuran matriks pertama adalah 4x2 , dan
matriks kedua 2x5 . Isi dari matriks didefinisikan di dalam kodingan. Matriks
nantinya akan berisi angka 1-20 ( tidak perlu dibuat filter angka).
2. Tampilkan matriks hasil perkalian tadi ke layar.
- Batu kedua adalah Amethyst. Batu mulia berwarna ungu mengkilat. Teka-tekinya
adalah:
1. Buatlah program C kedua dengan nama " 4b.c ". Program ini akan
mengambil variabel hasil perkalian matriks dari program "4a.c" (program
sebelumnya), dan tampilkan hasil matriks tersebut ke layar.
( Catatan! : gunakan shared memory)
- Batu ketiga adalah Onyx. Batu mulia berwarna hitam mengkilat. Pecahkan
teka-teki berikut!
1. Buatlah program C ketiga dengan nama " 4c.c ". Program ini tidak
memiliki hubungan terhadap program yang lalu.
2. Pada program ini, Norland diminta mengetahui jumlah file dan
folder di direktori saat ini dengan command " ls | wc -l ". Karena sudah belajar
IPC, Norland mengerjakannya dengan semangat.
( Catatan! : Harus menggunakan IPC Pipes)
Begitu batu terakhir berhasil didapatkan. Gemuruh yang semakin lama semakin
besar terdengar. Seluruh tempat berguncang dahsyat, tanah mulai merekah. Sebuah
batu yang di atasnya terdapat kotak kayu muncul ke atas dengan sendirinya.
Sementara batu tadi kembali ke posisinya. Tanah kembali menutup, seolah tidak
pernah ada lubang merekah di atasnya satu detik lalu.
Norland segera memasukkan tiga buah batu mulia Emerald, Amethys, Onyx pada
Peti Kayu. Maka terbukalah Peti Kayu tersebut. Di dalamnya terdapat sebuah harta
karun rahasia. Sampai saat ini banyak orang memburu harta karun tersebut.
Sebelum menghilang, dia menyisakan semua petunjuk tentang harta karun tersebut
melalui tulisan dalam buku catatannya yang tersebar di penjuru dunia. "One Piece
does exist".

## JAWABAN NO 4A

#### Deklarasi untuk ukuran matriks dan isi matriks


```
#define M 4
#define K 2
#define N 5
#define NUM_THREADS M * N

/* Global variables for threads to share */
int(*C)[10];

int A[M][K] = {{1, 1}, {1, 1}, {1, 1}, {1, 1}};
int B[K][N] = {{2, 2, 2, 2, 2}, {2, 2, 2, 2, 2}};

```

#### Struct berisi passing data ke thread

```
{
	int i; /* row */
	int j; /* column */
};
```

#### Shared Memory


```
key_t key = 1234;
int shmid = shmget(key, sizeof(int[10][10]), IPC_CREAT | 0666);
C = shmat(shmid, 0, 0);
```	
```
#### Menjalankan Perkalian matriks di THREAD

```
pthread_t workers[NUM_THREADS];
	
	/* We have to create M * N worker threads */
	for (i = 0; i < M; i++)
	{
		for (j = 0; j < N; j++) 
		{
			struct v *data = (struct v *) malloc(sizeof(struct v));
			data->i = i;
			data->j = j;
			/* Now we will create the thread passing it data as a paramater*/
			pthread_create(&workers[thread_counter], NULL, runner, data);
			pthread_join(workers[thread_counter], NULL);
			thread_counter++;
		}
	}
	
	/* Waiting for threads to complete */
	for (i = 0; i < NUM_THREADS; i++)
	{
	    pthread_join(workers[i], NULL);
	}
	
	for(i = 0; i < M; i++)
	{ 
		for(j = 0; j < N; j++)
		{ 
			printf("%d\t", C[i][j]);
		}
		printf("\n");
	}
	return 0;
}
```

#### Casting parameter ke struct v pointer
```
void *runner(void *ptr)
{	
	/* Casting paramater to struct v pointer */
	struct v *data = ptr;
	int i, sum = 0;
	
	for(i = 0; i < K; i++)
	{	
		sum += A[data->i][i] * B[i][data->j];
	}
	
	C[data->i][data->j] = sum;
	pthread_exit(0);
}

/*REFERENCES : 
https://gist.github.com/ozanyildiz/1863593
https://www.geeksforgeeks.org/multiplication-of-matrix-using-threads/
https://github.com/VYPRATAMA009/sisop-modul-3#26-shared-memory */

```

### Referensi   :
https://gist.github.com/ozanyildiz/1863593

## Output  :
![MODUL3](https://user-images.githubusercontent.com/61290164/78349728-3ddfa080-75ce-11ea-8ce0-242eca0ce963.PNG)

## SOAL NO. 4B


2. Setelah ditampilkan, berikutnya untuk setiap angka dari matriks
tersebut, carilah nilai faktorialnya , dan tampilkan hasilnya ke layar dengan
format seperti matriks.
Contoh: misal array [[1, 2, 3, 4], [5, 6, 7, 8], [9, 10, 11, 12], ...],
maka:
1 2 6 24
120 720 … …
...
( Catatan! : Harus menggunakan Thread dalam penghitungan
faktorial)




## JAWABAN NO. 4B

#### Melakukan Join Thread
```

void pthread_exit(void *rval_ptr);
int pthread_join(pthread_t thread, void **rval_ptr);
pthread_t thread1;

```

#### Shared Memory

```
    key_t key = 1234;
    int (*C)[10];
    int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    C = shmat(shmid, 0, 0);
```

#### Menampilkan Matriks dari jawaban 4a.c

```
```	
    int i,j;
	for(i=0;i<4;i++)
	{
		for(j=0;j<5;j++)
		{
			printf("%d\t", C[i][j]);
		}
		printf("\n");
	}
	printf("\n");
```

#### Hasil faktorial suatu matriks dari THREAD
```
```
	int newthread;
	newthread = pthread_create(&thread1, NULL, factorial, NULL);
	pthread_join(thread1,NULL);
	for(i=0;i<4;i++)
	{
		for(j=0;j<5;j++)
		{
			printf("%llu\t", output[i][j]);
		}
		printf("\n");
	}


	exit (EXIT_SUCCESS);
}
```
```
#### Menampilkan fungsi thread faktorial 

```
void *factorial()
{
    key_t key = 1234;
    int (*C)[10];
    int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    C = shmat(shmid, 0, 0);

	int i,j,k;
	for(i=0;i<4;i++)
	{
		for(j=0;j<5;j++)
		{
			unsigned long long f=1;
			for(k=1;k<=C[i][j];k++)
			{
				f= f+k;
				output[i][j] = f-1;
			}
		}
	}
}

```

## OUTPUT	:
![4B](https://user-images.githubusercontent.com/61290164/79011784-ff7a5080-7b8e-11ea-8caf-8aab25a4b5c9.PNG)

## SOAL 4C

- Batu ketiga adalah Onyx. Batu mulia berwarna hitam mengkilat. Pecahkan
teka-teki berikut!
1. Buatlah program C ketiga dengan nama " 4c.c ". Program ini tidak
memiliki hubungan terhadap program yang lalu.
2. Pada program ini, Norland diminta mengetahui jumlah file dan
folder di direktori saat ini dengan command " ls | wc -l ". Karena sudah belajar
IPC, Norland mengerjakannya dengan semangat.
( Catatan! : Harus menggunakan IPC Pipes)
Begitu batu terakhir berhasil didapatkan. Gemuruh yang semakin lama semakin
besar terdengar. Seluruh tempat berguncang dahsyat, tanah mulai merekah. Sebuah
batu yang di atasnya terdapat kotak kayu muncul ke atas dengan sendirinya.
Sementara batu tadi kembali ke posisinya. Tanah kembali menutup, seolah tidak
pernah ada lubang merekah di atasnya satu detik lalu.
Norland segera memasukkan tiga buah batu mulia Emerald, Amethys, Onyx pada
Peti Kayu. Maka terbukalah Peti Kayu tersebut. Di dalamnya terdapat sebuah harta
karun rahasia. Sampai saat ini banyak orang memburu harta karun tersebut.
Sebelum menghilang, dia menyisakan semua petunjuk tentang harta karun tersebut
melalui tulisan dalam buku catatannya yang tersebar di penjuru dunia. "One Piece
does exist".


## JAWABAN 4C


```
#include <stdlib.h>
#include <unistd.h>

int pid;
int pipe1[2];

int main()
{
  if (pipe(pipe1) == -1)
    exit(1);

  if ((fork()) == 0) 
  {
    // output to pipe1
    dup2(pipe1[1], 1);
    // close fds
    close(pipe1[0]);
    close(pipe1[1]);
    // exec
    char *argv1[] = {"ls", NULL};
		execv("/bin/ls", argv1);
  }

  else
  {
    // input from pipe1
    dup2(pipe1[0], 0);

    // close fds
    close(pipe1[0]);
    close(pipe1[1]);

    // exec
    char *argv1[] = {"wc", "-l", NULL};
		execv("/usr/bin/wc", argv1);
  }
}

```

## OUTPUT	:
![4C](https://user-images.githubusercontent.com/61290164/79011788-00ab7d80-7b8f-11ea-8813-03e21f29eb34.PNG)
