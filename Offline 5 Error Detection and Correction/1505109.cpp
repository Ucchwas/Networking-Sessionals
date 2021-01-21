#include<bits/stdc++.h>
#include<windows.h>
using namespace std;

HANDLE  hConsole;
int errorBitPosition[1000];
int errorNumbers;


void setRed()
{
    SetConsoleTextAttribute(hConsole, 4);
}

void setGreen()
{
    SetConsoleTextAttribute(hConsole, 2);
}

void setCyan()
{
    SetConsoleTextAttribute(hConsole, 11);
}

void setBack()
{
    SetConsoleTextAttribute(hConsole, 7);
}

int binaryToDecimal(int n)
{
    int num = n;
    int dec_value = 0;
    int base = 1;
    int temp = num;

    while (temp)
    {
        int last_digit = temp % 10;
        temp = temp/10;
        dec_value += last_digit*base;
        base = base*2;
    }
    return dec_value;
}

string decToBinary(int n)
{
    string result;
    for (int i = 7; i >= 0; i--)
    {
        int k = n >> i;
        if (k & 1)
            result.append("1");
        else
            result.append("0");
    }
    return result;
}

bool isPowerOfTwo(int n)
{
    return (ceil(log2(n)) == floor(log2(n)));
}

int randomNumGenerator(int limit)
{
    srand(time(0));

    int r = rand()%limit;

    return r;
}

vector <string> createDataBlock(int m, string data)
{
    //  int count = 1;
    string message = "";
    vector <string> block;
    for(int i = 0; i < data.length(); i++)
    {
        int temp = (int)data[i];
        string bin = decToBinary(temp);
        message.append(bin);
    }

    while(true)
    {
        if((message.length() % (m*8)) != 0)
        {
            message.append(decToBinary((int)'~'));
            data += "~";
        }
        else
            break;
    }

    cout << endl << "data string after padding: " << data << endl << endl;

    int numberOfBlocks = message.length() / (m*8);
    for(int i=0; i<numberOfBlocks; i++)
    {
        block.push_back(message.substr(m*i*8, m*8));
    }

    cout << "data block (ascii code of m characters per row): " << endl;
    for(int i=0; i<numberOfBlocks; i++)
    {
        cout << block[i] << endl;
    }
    return block;
}

vector <string> initializeCheckBits(vector <string> block)
{
    int messageLength = block[0].size();

    for(int i=0; i<block.size(); i++)
    {
        string temp = "";
        int blockIndex = 0;
        int tempIndex = 0;
        while(true)
        {
            if((blockIndex) == messageLength)
                break;

            if(isPowerOfTwo(tempIndex+1))
            {
                //cout << "jhgsdjkgskaf" << endl;
                temp += "0";
                tempIndex++;
            }
            else
            {
                temp += block[i][blockIndex];
                tempIndex++;
                blockIndex++;
            }
        }
        block[i] = temp;
    }

    return block;
}

string addCheckBits(string block)
{
    bool isValid = false;
    int checkParity = 0;
    int i;
    for(i=0; i<block.size(); i++)
    {
        if(!isPowerOfTwo(i+1))
        {
            continue;
        }
        int j = i+1;
        int step = j;
        int b = i;
        checkParity = 0;
        while(b<block.size())
        {
            if(step == j)
            {
                isValid = true;
            }
            if(isValid)
            {
                if(block[b]=='1')
                    checkParity += 1;
                b=b+1;
                step--;
            }
            if(!isValid)
            {
                step++;
                b++;
            }
            if(step == 0)
            {
                isValid = false;
            }
        }
        if(checkParity%2 ==1)
        {
            block[i] = '1';
        }
    }
    return block;
}

string serializeDataBlock(vector <string> block)
{
    string result = "";

    for(int i=0; i<block[0].size(); i++)
    {
        for(int j=0; j<block.size(); j++)
        {
            result += block[j][i];
        }
    }

    cout << endl << "data bits after column-wise serialization: " << endl;
    cout << result << endl;

    return result;
}

string addCRCChecksum(string message, int p)
{
    string polynomial = to_string(p);
    int polynomialSize = polynomial.size();
    string remainder = "";
    string temp = message;

    for(int i=0; i<polynomialSize-1; i++)
    {
        temp += "0";
    }

    int firstValidIndex;

    for(int i=0; i<=temp.size()-polynomialSize; i++)
    {
        if(temp[i] == '1')
        {
            for(int j=i; j<i+polynomialSize; j++)
            {
                if(((temp[j] == '0') && (polynomial[j-i] == '1')) || ((temp[j] == '1') && (polynomial[j-i] == '0')))
                {
                    temp[j] = '1';
                 }
                else
                {
                    temp[j] = '0';
                }
            }
        }
    }
    int idx = 0;

    while(true)
    {
        if(temp[idx] == '1')
            break;
        if(idx == temp.size()-1)
            break;
        idx++;
    }

    for(int x=idx; x<temp.size(); x++)
    {
        remainder += temp[x];
    }

    while(remainder.size() < polynomialSize-1)
    {
        remainder = "0" + remainder;
    }

    message += remainder;

    return message;
}

string transmitData(string message, float probability)
{
    int numberOfErrorBits = probability * message.size();
    errorNumbers = numberOfErrorBits;
    int indexOfErrorBits[numberOfErrorBits];
    srand(time(0));

    for(int i=0; i<numberOfErrorBits; i++)
    {
        indexOfErrorBits[i] = rand() % message.size();
        if(message[indexOfErrorBits[i]] == '0')
            message[indexOfErrorBits[i]] = '1';
        else
            message[indexOfErrorBits[i]] = '0';
    }
    int n = sizeof(indexOfErrorBits)/sizeof(indexOfErrorBits[0]);
    sort(indexOfErrorBits, indexOfErrorBits+n);

    int k;
    for(k=0; k<numberOfErrorBits; k++)
    {
        errorBitPosition[k] = indexOfErrorBits[k];
    }
    errorBitPosition[k] = NULL;
    int count = 0;
    cout << endl << endl << "received frame: " << endl;
    for(int i=0; i<message.size(); i++)
    {
        if(i == indexOfErrorBits[count])
        {
            setRed();
            cout << message[i];
            count++;
            setBack();
        }
        else
            cout << message[i];
    }
    return message;
}

bool detectError(string message, int p)
{
    string polynomial = to_string(p);
    int polynomialSize = polynomial.size();
    string remainder = "";
    string temp = message;

    for(int i=0; i<=temp.size()-polynomialSize; i++)
    {
        if(temp[i] == '1')
        {
            for(int j=i; j<i+polynomialSize; j++)
            {
                if(((temp[j] == '0') && (polynomial[j-i] == '1')) || ((temp[j] == '1') && (polynomial[j-i] == '0')))
                {
                    temp[j] = '1';
                }
                else
                {
                    temp[j] = '0';
                }
            }
        }
    }
    int idx = 0;

    while(true)
    {
        if(temp[idx] == '1')
            return true;
        if(idx == temp.size()-1)
            break;
        idx++;
    }
    return false;
}

vector<string> deserializeMessage(string message, int m, int p, vector<string> blck)
{
    string polynomial = to_string(p);
    int sizeOfPoly = polynomial.size();
    int colorIndexCounter = 0;
    int errorIndexCounter = 0;
    int messageCounter = 0;
    int idx = message.size() - sizeOfPoly + 1;
    message = message.substr(0, idx);
    int row = blck.size();
    int x;

    vector<string> blocks;
    for(int i=0; i<row; i++)
        blocks.push_back("");

    for(x=0; x<blck[0].size(); x++)
    {
        for(int y=0; y<row; y++)
        {
            blocks[y] += message[messageCounter];
            messageCounter++;
        }
    }

    cout << endl << "data block after removing CRC checkSum bits: " << endl;
    for(int i=0; i<row; i++)
    {
        for(int j=0; j<blck[0].size(); j++)
        {
            if(blocks[i][j] != blck[i][j])
            {
                setRed();
                cout << blocks[i][j];
                setBack();
            }
            else
                cout << blocks[i][j];
        }
        cout << endl;
    }

    return blocks;
}

vector<string> errorCorrection(vector<string> block)
{
    for(int i=0; i<block.size(); i++)
    {
        string index = "";
        int position;
        for(int j=block[0].size()-1; j>0; j--)
        {
            if(isPowerOfTwo(j+1))
            {
                index += block[i][j];
            }
        }
        position = stoi(index);
        position = binaryToDecimal(position);

        if(position != 0)
        {
            if(block[i][position-1] == '0')
                block[i][position-1] = '1';
            else
                block[i][position-1] = '0';
        }
    }
    int len = block[0].size();
    for(int i=0; i<block.size(); i++)
    {
        string temp = "";
        for(int j=0; j<len; j++)
        {
            if(!isPowerOfTwo(j+1))
            {
                temp += block[i][j];
            }
        }
        block[i] = temp;
    }

    return block;
}

void generateDataString(vector<string> block, int m)
{
    cout << endl << endl;
    for(int i=0; i<block.size(); i++)
    {
        for(int j=0; j<m; j++)
        {
            string temp = "";
            int ascii;
            char letter;
            for(int k=j*8; k<j*8+8; k++)
            {
                temp += block[i][k];
            }
            ascii = stoi(temp);
            letter = ascii;
            cout << letter;
        }
    }
}


int main()
{
    string data;
    int m;
    float probability;
    int polynomial;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    cout << "enter data string: ";
    getline(cin, data);
    cout << "enter number of bytes in a row (m): ";
    cin >> m;
    cout << "enter probability: (p): ";
    cin >> probability;
    cout << "enter generator polynomial: ";
    cin >> polynomial;

    vector <string> block = createDataBlock(m, data);
    vector <string> blockWithInitialCheckBits = initializeCheckBits(block);

    for(int i=0; i<blockWithInitialCheckBits.size(); i++)
    {
        block[i] = addCheckBits(blockWithInitialCheckBits[i]);
    }
    cout << endl << "data block after adding check bits: " << endl;
    for(int i=0; i<block.size(); i++)
    {
        for(int j=0; j<block[i].size(); j++)
        {
            if(isPowerOfTwo(j+1))
                setGreen();
            else
                setBack();
            cout << block[i][j];
        }
        cout << endl;
    }

    string serializedMessage = serializeDataBlock(block);
    int seriMsgsize = serializedMessage.size();
    serializedMessage = addCRCChecksum(serializedMessage, polynomial);

    cout << endl << "data bits after appending checkSum: " << endl;
    for(int i=0; i<seriMsgsize; i++)
        cout << serializedMessage[i];
    for(int i=seriMsgsize; i<serializedMessage.size(); i++)
    {
        setCyan();
        cout << serializedMessage[i];
    }
    setBack();

    string receivedMessage = transmitData(serializedMessage, probability);
    if(detectError(receivedMessage, polynomial))
        cout << endl << endl << "result of CRC checkSum matching: error detected" << endl;
    else
        cout << endl << endl << "result of CRC checkSum matching: no error detected" << endl;

    vector <string> receivedBlocks = deserializeMessage(receivedMessage, m, polynomial, block);

    for(int i=0; i<receivedBlocks.size(); i++)
    {
        receivedBlocks[i] = addCheckBits(receivedBlocks[i]);
    }

    receivedBlocks = errorCorrection(receivedBlocks);
    cout << endl << endl;

    cout << "data block after removing check bits: " << endl;
    for(int i=0; i<receivedBlocks.size(); i++)
    {
        for(int j=0; j<receivedBlocks[i].size(); j++)
        {
            cout << receivedBlocks[i][j];
        }
        cout << endl;
    }

    generateDataString(receivedBlocks, m);

    cout << endl << endl << endl;

    return 0;
}


