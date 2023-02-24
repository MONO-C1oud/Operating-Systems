### Name: Muhammad Taha Qaiser
### Roll number: 21K-4779
### Section: BCY-4A

# Objectives:

- Changing the name of the kernel to anything you want
- Creating a system call
- Checking the results of the above two things

---

# Procedure:

  ## Prerequisites:
  
Switch to the root user so that you dont have to type `sudo` again and again
    
    sudo su
  
Run these commands to install all the stuff required to compile the kernel:
  
    apt-get install gcc
    apt-get install libncurses5-dev
    apt-get install bison
    apt-get install flex
    apt install make
    apt-get install libssl-dev
    apt-get install libelf-dev
    add-apt-repository "deb http://archive.ubuntu.com/ubuntu $(lsb_release -sc) main universe"
    apt-get update
    apt-get upgrade

Download the kernel version of your choice from `https://kernel.org/`. I used version 5.4.232. Download the tar.xz and extract it like so:

---
![1 downloading and extracting kernel](https://user-images.githubusercontent.com/115342166/221254019-e8374278-87a2-418d-abf2-48d48c7d6dd6.PNG)
---

## Achieving objectives:

Edit the `Makefile` and change the `EXTRAVERSION` variable to anything you want. I assigned it my roll number (21k-4779)

---
![2 naming kernel 2](https://user-images.githubusercontent.com/115342166/221254041-07b4a35f-2db9-4b8a-a5db-9fec6f1e20cc.PNG)
---

OR

Change the CONFIG_LOCALVERSION variable to a string of your choice. I assigned my roll number to this too.

---
![2 setting the kernel name](https://user-images.githubusercontent.com/115342166/221254052-3b6d65c8-6c93-44dd-acab-64ae9f9a0f01.PNG)
---

Edit the `./arch/x86/entry/syscalls/syscall_64.tbl` file and add your system call's information. 
Only choose a number that is allowed (for example, I couldn't choose between 387-423 according to the screenshot below)
The second column shows if the system call is 32 bit or 64 bit or for both (common)

---
![3 system call table](https://user-images.githubusercontent.com/115342166/221254056-9356e040-028e-499e-8642-8828e13253a4.PNG)
---

Now, to create the system call itself, edit the `./kernel/sys.c` file. Scroll down to the end and create a function like:
  
    SYSCALL_DEFINE0(syscall_name) {}

Here, SYSCALL_DEFINE0 means that we are defining a system call with 0 arguments. In the brackets we mention the name of our system call which
was `hello` in my case. The `printk()` function is used to print a string in the kernel logs:

![4 Making system call](https://user-images.githubusercontent.com/115342166/221254069-bda93cc7-cef7-4e90-8806-2ba064a28ecd.PNG)
---

copy your original config file from the `/boot` directory to the new kernel's directory:

![5 copying the old config](https://user-images.githubusercontent.com/115342166/221254085-02a4acad-3701-4775-b1f3-91b3bcee29f4.PNG)
---

run these commands to compile the kernel:
  
    make clean -j6
    yes "" | make oldconfig -j6
    make -j6
    make modules_install install

change -j6 to the number of cores you have assigned to your virtual machine (it can be checked using the command `lscpu`), for example -j4 if you have
assigned 4 cores to your virtual machine:

---
![6 make clean](https://user-images.githubusercontent.com/115342166/221254092-0ca74d5d-9ddb-47d4-bd25-fee5657efa94.PNG)

![7 make oldconfig](https://user-images.githubusercontent.com/115342166/221254110-7ec1d906-4084-4976-bff8-051bbcc1fa66.PNG)

![8 compiling the kernel](https://user-images.githubusercontent.com/115342166/221254119-5020a58b-56da-437b-adac-62c139538fdf.PNG)

![9 make modules](https://user-images.githubusercontent.com/115342166/221254135-2be386c2-4a85-4aca-ae56-32870e6ba5e2.PNG)
---

Restart your virtual machine and hold down the shift key to make the GRUB bootloader pop up:

---
![10 grub](https://user-images.githubusercontent.com/115342166/221254182-0fb2ad74-4f4e-4ddb-be44-951e269a8870.PNG)
---

Select your newly compiled kernel from the `Advanced options for Ubuntu` menu:

---
![11 grub advanced](https://user-images.githubusercontent.com/115342166/221254206-e60f2a52-17bb-4665-90f3-7e6342fec45a.PNG)
---

After booting with the new kernel, open the terminal and check the kernel name using `uname -r`:

---
![12 uname roll no](https://user-images.githubusercontent.com/115342166/221254248-b56c8fb1-879d-4725-be1b-5275af4cc10a.PNG)
---

To check your custom system call, create a new c source file which calls your syscall:

---
![13 test program](https://user-images.githubusercontent.com/115342166/221254273-13c798bb-b899-4593-9448-ac5bfedf57c2.PNG)
---

Compile the source file and give the executable permission to execute. Run the executable and then check the kernel logs using `dmesg` to see if your
message was printed.

---
![14 hello world](https://user-images.githubusercontent.com/115342166/221254289-6345abb4-00af-4e47-81a9-44a18ad2b768.PNG)
---
