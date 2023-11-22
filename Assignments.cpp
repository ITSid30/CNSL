CNS Assignments 


Assign 2 RSA: 

#include <bits/stdc++.h>
using namespace std;

int publicKey;
int privateKey;
int n;

void setKeys() {
  int p, q;
  cout << "\nEnter any 2 big prime numbers : " << endl;
  cin >> p >> q;

  n = p * q;
  int phi = (p - 1) * (q - 1);
  int e = 2;

  while (true) {
    if (__gcd(e, phi) == 1)
      break;
    else
      e++;
  }
  publicKey = e; // Found the public key

  int d = 2;
  while (true) {
    if ((d * e) % phi == 1) {
      break;
    }
    d++;
  }
  privateKey = d; // Found the private Key
}

int encrypt(long long int msg) {
  int e = publicKey;
  long long int cipher = 1;
  while (e--) { // using formula for encryption c = m^e mod n
    cipher *= msg;
    cipher %= n;
  }
  return cipher;
}

long long int decrypt(int encoded) {
  int d = privateKey;
  long long int plain = 1;
  while (d--) { // using formula for decryption m = c^d mod n
    plain *= encoded;
    plain %= n;
  }
  return plain;
}

vector<int> encoder(string &plain) {
  vector<int> cipher;
  for (char ch : plain) {
    cipher.push_back(encrypt(int(ch))); // calling encrypt function
  }
  return cipher;
}

string decoder(vector<int> &coded) {
  string decipher;
  for (auto num : coded) {
    decipher += decrypt(num);
  }
  return decipher;
}

int main() {
  setKeys();

  string plain;
  cout << "Enter plain Text Message: ";
  cin >> plain;
  cout << "\n\nPlain Text is : " << plain << endl;

  cout << "\nThe Cipher form of plain text is : \n";
  vector<int> coded = encoder(plain);
  for (int a : coded)
    cout << a;
  cout << endl;

  cout << "\nThe Decipher form of message is : \n\t";
  cout << decoder(coded) << "\n" << endl;
}



Assign 3: 

#include <bits/stdc++.h>
using namespace std;

string key;
// vector<int> hash;
void xor_op(string &str) {
  for(int i=0;i<str.size();i++) {
    str[i] = str[i] ^ key[i];
  }
}

string encrypt(string &plain, vector<int> &hash) 
{
  // string key = plain;
  int n = plain.size();
  string cipher = "";
  for(int i=0;i<plain.size();i++)
    {
      if(i %2 == 0) {
        plain[i] = (plain[i] - 97 + 3) % 26 + 65;
      }
      else plain[i] = abs(plain[i] -97 - 3) % 26 + 65;
      // cout << plain[i] << " ";
    }
  
  xor_op(plain);
  return plain;
}

string decrypt(string &encoded, vector<int> &hash) {
  int n = encoded.size();
  string decipher = "";

  xor_op(encoded);

  for(int i=0;i<encoded.size();i++)
    {
      if(i %2 == 0) {
        encoded[i] = abs(encoded[i] - 65 - 3) % 26 + 97;
      }
      else encoded[i] = (encoded[i] -65 + 3) % 26 + 97;
      // cout << encoded[i] << " ";
    }

  return encoded;
}

int main()
{
  string plain;
  cout << "\nEnter a plain text message : ";
  getline(cin, plain);
  int n = plain.size();
  vector<int> hash(n, 0); 
  key = plain;
  
  cout << "\nPlain text : " << plain << endl;
  string encoded = encrypt(plain, hash);
  cout << "\n\nThe Encipher of text : " << encoded << endl;
  string decoded = decrypt(plain, hash);
  cout << "\n\nThe Decipher of the Encrypted text is : " << decoded << endl;
  return 0;
}


Assign 4:

#include <iostream>
using namespace std;

long long int modular_pow(long long int base, long long int exponent, long long int modulus) {
  if (modulus == 1)
    return 0;
  long long int result = 1;
  base = base % modulus;
  while (exponent > 0) {
    if (exponent % 2 == 1)
      result = (result * base) % modulus;
    exponent = exponent >> 1; // Equivalent to exponent /= 2
    base = (base * base) % modulus;
  }
  return result;
}

int main() {
  long long int p, g, a, b, c, d, x, y, xe, ye, ka, kb, kea, keb;
  cout << "Enter a prime number (P): ";
  cin >> p;
  cout << "Enter a number (G): ";
  cin >> g;
  cout << endl;
  cout << "Enter Alice's private number (a): ";
  cin >> a;
  cout << "Enter Bob's private number (b): ";
  cin >> b;
  cout << endl;
  cout << "Enter Eve's selected private number for Bob from Alice (c): ";
  cin >> c;
  cout << "Enter Eve's selected private number for Alice from Bob (d): ";

  cin >> d;
  cout << endl;
  x = modular_pow(g, a, p);
  y = modular_pow(g, b, p);
  cout << "Alice published key: " << x << endl;
  cout << "Bob published key: " << y << endl;
  xe = modular_pow(g, c, p);
  ye = modular_pow(g, d, p);
  cout << "Eve published value for Alice: " << xe << endl;
  cout << "Eve published value for Bob: " << ye << endl;
  ka = modular_pow(xe, a, p);
  kea = modular_pow(x, c, p);
  kb = modular_pow(ye, b, p);
  keb = modular_pow(y, d, p);
  cout << "Alice computed (S1): " << ka << endl;
  cout << "Eve computed key for Alice (S1): " << kea << endl;
  cout << "Bob computed (S2): " << kb << endl;
  cout << "Eve computed key for Bob (S2): " << keb << endl;
  return 0;
}



Assign 5:

// Java program to calculate SHA-1 hash value

import java.math.BigInteger;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

class Main {
    public static String encryptThisString(String input)
    {
        try {
            // getInstance() method is called with algorithm SHA-1
            MessageDigest md = MessageDigest.getInstance("SHA-1");

            // digest() method is called
            // to calculate message digest of the input string
            // returned as array of byte
            byte[] messageDigest = md.digest(input.getBytes());

            // Convert byte array into signum representation
            BigInteger no = new BigInteger(1, messageDigest);

            // Convert message digest into hex value
            String hashtext = no.toString(16);

            // Add preceding 0s to make it 32 bit
            while (hashtext.length() < 32) {
                hashtext = "0" + hashtext;
            }

            // return the HashText
            return hashtext;
        }

        // For specifying wrong message digest algorithms
        catch (NoSuchAlgorithmException e) {
            throw new RuntimeException(e);
        }
    }

    // Driver code
    public static void main(String args[]) throws
                                       NoSuchAlgorithmException
    {

        System.out.println("HashCode Generated by SHA-1 for: ");

        String s1 = "Siddhesh Bajad";
        System.out.println("\n" + s1 + " : " + encryptThisString(s1));

        String s2 = "hello world";
        System.out.println("\n" + s2 + " : " + encryptThisString(s2));
    }
}


Assign 7: 

#include <bits/stdc++.h>
using namespace std;

int publicKey(int Xa, int alpha, int q)
{
  int Ya = 1;
  while(Xa > 0)
    {
      Ya *= alpha;
      Ya %= q;
      Xa--;
    }
  return Ya;
}

int sign1(int alpha, int K, int q)
{
  int s1 = 1;
  while(K > 0)
    {
      s1 *= alpha;
      s1 %= q;
      K--;
    }
  return s1;
}

int inverse(int K, int mod)
{
  int k1 = 1;
  while(K*k1 % mod != 1) {
    k1++;
  }
  return k1;
}

int sign2(int K1, int m, int Xa, int S1, int mod)
{
  int temp = m - Xa*S1;
  int s2 = ((K1) * abs(temp)) % mod;
  if(temp < 0) {
    return mod - s2;
  }
  return s2;
}

int verify1(int alpha, int m, int q)
{
  int v1 = 1;
  while(m > 0)
    {
      v1 *= alpha;
      v1 %= q;
      m--;
    }
  return v1;
}

int verify2(int Ya, int S1, int S2, int q)
{
  int v2 = 1;
  long long term1 = pow(Ya, S1);
  long long term2 = pow(S1, S2);
  return (term1 * term2) % q;
}

int main(){
  // ld p,e1,d,m,r,MOD;
  // cin>>p>>e1>>d>>m>>r;
  // ld e2,s1,s2,v1,v2,a,b;
  // e2=powerStrings(to_string(e1),to_string(d),p);if(e2<0)e2+=p;
  // s1=powerStrings(to_string(e1),to_string(r),p);if(s1<0)s1+=p;
  // s2=(((m-d*s1)%(p-1))*ModInv(r,p-1))%(p-1);if(s2<0)s2+=(p-1);
  // v1=powerStrings(to_string(e1),to_string(m),p);if(v1<0)v1+=p;
  // a=powerStrings(to_string(e2),to_string(s1),p);if(a<0)a+=p;
  // b=powerStrings(to_string(s1),to_string(s2),p);if(b<0)b+=p;
  // v2=(a*b)%p;
  // cout<<"e2="<<e2<<"\n";
  // cout<<"s1="<<s1<<"\n";
  // cout<<"s2="<<s2<<"\n";
  // cout<<"v1="<<v1<<"\n";
  // cout<<"v2="<<v2<<"\n";

  int q, alpha, Xa, Ya, m, K;
  cout << "\nEnter Public elements for Elgamal Algorithm (q, alpha) : ";
  cin >> q >> alpha;
  cout << "Enter Private Key for User : ";
  cin >> Xa;
  cout << "Enter Hash value of message ie. m : ";
  cin >> m;
  cout << "Enter a Random Character K : ";
  cin >> K;
  
  Ya = publicKey(Xa, alpha, q);
  cout << "\nPublic Key for User : Ya : " << Ya << endl;
  // Digital Signature generation
  int S1, S2;
  S1 = sign1(alpha, K, q);
  cout << "\nS1 = " << S1 << endl;
  int K1 = inverse(K, q-1);
  cout << "\nK inverse : K1 = " << K1 << endl;
  S2 = sign2(K1, m, Xa, S1, q-1);
  cout << "\nS2 = " << S2 << endl;
  // Digital Signature is (S1, S2)
  cout << "\nDigital Signature is : (S1, S2) => ( " << S1 << " , " << S2 << " ) \n"; 
  // Verification
  int v1, v2;
  v1 = verify1(alpha, m, q);
  v2 = verify2(Ya, S1, S2, q);
  cout << "\nV1 = " << v1 << endl;
  cout << "\nV2 = " << v2 << endl;
  if(v1 == v2) cout << "\nVerified\n";
  else cout << "\nNot Verified\n";
}




Assign 8:

#include <bits/stdc++.h>
using namespace std;

int publicKey;
int privateKey;
int publicKeyB, privateKeyB;
int n, m;

void setKeys() {
  int p, q;
  cout << "\nEnter any 2 big prime numbers : " << endl;
  cin >> p >> q;

  n = p * q;
  int phi = (p - 1) * (q - 1);
  int e = 2;

  while (true) {
    if (__gcd(e, phi) == 1)
      break;
    else
      e++;
  }
  publicKey = e; // Found the public key

  int d = 2;
  while (true) {
    if ((d * e) % phi == 1) {
      break;
    }
    d++;
  }
  privateKey = d; // Found the private Key
}

void setKeysB() {
  int p, q;
  cout << "\nEnter any 2 big prime numbers : " << endl;
  cin >> p >> q;

  m = p * q;
  int phi = (p - 1) * (q - 1);
  int e = 2;

  while (true) {
    if (__gcd(e, phi) == 1)
      break;
    else
      e++;
  }
  publicKeyB = e; // Found the public key

  int d = 2;
  while (true) {
    if ((d * e) % phi == 1) {
      break;
    }
    d++;
  }
  privateKeyB = d; // Found the private Key
}

int encrypt(long long int msg) {
  int e = privateKey;
  long long int cipher = 1;
  while (e--) { // using formula for encryption c = m^e mod n
    cipher *= msg;
    cipher %= n;
  }
  return cipher;
}

long long int decrypt(int encoded) {
  int d = publicKey;
  long long int plain = 1;
  while (d--) { // using formula for decryption m = c^d mod n
    plain *= encoded;
    plain %= n;
  }
  return plain;
}

vector<int> encoder(string &plain) {
  vector<int> cipher;
  for (char ch : plain) {
    cipher.push_back(encrypt(int(ch))); // calling encrypt function
  }
  return cipher;
}

string decoder(vector<int> &coded) {
  string decipher;
  for (auto num : coded) {
    decipher += decrypt(num);
  }
  return decipher;
}

int encryptB(long long int msg) {
  int e = publicKeyB;
  long long int cipher = 1;
  while (e--) { // using formula for encryption c = m^e mod n
    cipher *= msg;
    cipher %= m;
  }
  return cipher;
}

long long int decryptB(int encoded) {
  int d = privateKeyB;
  long long int plain = 1;
  while (d--) { // using formula for decryption m = c^d mod n
    plain *= encoded;
    plain %= m;
  }
  return plain;
}

vector<int> encoderB(string &plain) {
  vector<int> cipher;
  for (int ch : plain) {
    cipher.push_back(encryptB(ch)); // calling encrypt function
  }
  return cipher;
}

vector<long long int> UserBvector;
string decoderB(vector<int> &coded) {
  string decipher;
  for (auto num : coded) {
    decipher += decryptB(num);
    UserBvector.push_back(decrypt(num));
  }
  return decipher;
}

int main() {
  setKeys();

  // user A encryption using PRivate Key
  string plain;
  cout << "Enter plain Text Message from user A: ";
  cin >> plain;
  cout << "\n\nPlain Text is : " << plain << endl;

  cout << "\nThe Cipher form of plain text is : \n";
  vector<int> coded = encoder(plain);
  string code = "";
  for (int a : coded) {
    cout << a;
    code += to_string(a);
    cout << "char dwekd : " << code << endl;
  }
  cout << endl;

  cout << code << endl;
  // User B encryption using Public Key of B
  cout << "\nPassing the coded Cipher message to User B" << endl;
  setKeysB();
  cout << "\nEncrypted Cipher using Public Key of B : " << endl;
  vector<int> doublecoded = encoderB(code);
  for (int a : doublecoded) {
    cout << a;
  }
  cout << endl;

  // User B decryption using Private Key of B
  cout << "\nIntermediate Message decrypted by user B using his private key is : ";
  string temp = decoderB(doublecoded);
  cout << temp << "\n" << endl;
  vector<int> doublecipher;
  // cout << "\nUserB string ";
  // for(auto a: UserBvector)
  //   {
  //     cout << a << endl;
  //   }
  for (int a : doublecoded) {
    doublecipher.push_back(a);
  }
  

  // user A decryption using Public Key of A
  cout << "\nThe Decipher form of message using Public Key of A is : \n";
  cout << decoder(coded) << "\n" << endl;
}



Assign 9:  Image Encryption


import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.Scanner;

public class Encryption {
    public static void main(String args[]) 
            throws FileNotFoundException, IOException
    {
        
        Scanner sc = new Scanner(System.in);
        int key;
        System.out.print("Enter Key for Encryption: ");
        key = sc.nextInt();
        
//        System.out.println("\nEnter Image path for encryption: ");
//        String path = sc.nextLine();
        
        FileInputStream fis = new FileInputStream("C:\\Users\\siddh\\Downloads\\11186.jpg");
        
        byte data[] = new byte[fis.available()];
        
        fis.read(data);
        
        int i = 0;
        for(byte b : data) {
            data[i] = (byte)(b ^ key);
            i++;
        }
        
        FileOutputStream fos = new FileOutputStream("C:\\Users\\siddh\\Downloads\\11186.jpg");
        
        fos.write(data);
        
        fos.close();
        fis.close();
        
        System.out.println("\nEncryption Done !");
        
    }
}



import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.Scanner;

public class Decryption {
    public static void main(String args[]) 
            throws FileNotFoundException, IOException
    {
        
        Scanner sc = new Scanner(System.in);
        int key;
        System.out.print("Enter Key for Decryption: ");
        key = sc.nextInt();
        
//        System.out.println("\nEnter Image path for Decryption: ");
//        String path = sc.nextLine();
        
        FileInputStream fis = new FileInputStream("C:\\Users\\siddh\\Downloads\\11186.jpg");
        
        byte data[] = new byte[fis.available()];
        
        fis.read(data);
        
        int i = 0;
        for(byte b : data) {
            data[i] = (byte)(b ^ key);
            i++;
        }
        
        FileOutputStream fos = new FileOutputStream("C:\\Users\\siddh\\Downloads\\11186.jpg");
        
        fos.write(data);
        
        fos.close();
        fis.close();
        
        System.out.println("\nDecryption Done !");
        
    }
}
