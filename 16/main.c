#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <assert.h>
#include <math.h>

typedef unsigned short int USINT;
typedef unsigned int UINT;
typedef unsigned long long int ULLI;
typedef long long int LLI;

#if 1
#define INPUT_FILE "input.txt"
#else
#define INPUT_FILE "sample.txt"
#endif 

#define LINE_CAP 10000
#define PACKET_CAP 1024

typedef struct _packet
{
    int ver;
    int typeID;
    ULLI literal;
    int lengthTypeID;
    struct _packet *subpackets;
    size_t subpackets_sz;
} Packet; 

Packet pkts[PACKET_CAP];
int pkts_sz = 0;

ULLI bin2decULLI(char* bin){
    ULLI dec=0;
    for (size_t i = 0; i<strlen(bin); i++) dec += (ULLI)(bin[i]-'0')<<(ULLI)(strlen(bin)-i-1);
    return dec;
}

int bin2dec(char* bin){
    int dec=0;
    for (size_t i = 0; i<strlen(bin); i++) dec+=(bin[i]-'0')<<(strlen(bin)-i-1);
    return dec;
}

char *hex2bin(char* line)
{
    int line_len = strlen(line);
    char* temp = (char*)malloc(line_len*4+1);
    int num;
    for (size_t j=0,i=0; i < line_len; i++,j+=4)
    {
        if (line[i]>='0' && line[i]<='9') num = line[i] - '0';
        else num = line[i] - 'A' + 10;
        for (int k=3; k>=0; k--) temp[j+k] = ((num&(1<<(3-k)))>>(3-k)) + '0';
    }
    return temp;
}

Packet parseLiteral(char* bits, int *idx, int ver, int typeID)
{
    int i = *idx;
    int count=0;
    Packet lit;
    lit.ver=ver;lit.typeID=typeID;
    while (bits[i] - '0')
    {
        i+=5;
        count++;
    }
    char literal[(count+1)*4+1];
    size_t j;
    for (i = 0,j=0; i < (count+1)*5; i++,j++)
    {
        if (i%5 && i>0) literal[j]=bits[i+*idx];
        else j--;
    }
    literal[(count+1)*4] = '\0';
    *idx += i;
    
    lit.literal = bin2decULLI(literal);
    return lit;
}

ULLI subpacketSum(int sz, Packet sp[sz])
{
    if(sz==1) return sp[0].literal;
    ULLI sum=0;
    for (size_t i = 0; i < sz; i++) sum+=sp[i].literal;
    return sum;
}

ULLI subpacketProd(int sz, Packet sp[sz])
{
    if(sz==1) return sp[0].literal;
    ULLI prod=1;
    for (size_t i = 0; i < sz; i++) prod = prod * sp[i].literal;
    return prod;
}

ULLI subpacketMin(int sz, Packet sp[sz])
{
    if(sz==1) return sp[0].literal;
    ULLI min=LLONG_MAX;
    for (size_t i = 0; i < sz; i++) if (sp[i].literal<min) min = sp[i].literal;
    return min;
}

ULLI subpacketMax(int sz, Packet sp[sz])
{
    if(sz==1) return sp[0].literal;
    ULLI max=0;
    for (size_t i = 0; i < sz; i++) if (sp[i].literal>max) max = sp[i].literal;
    return max;
}

Packet parseOperator(char *binary_packet, int *idx, int ver, int typeID)
{
    size_t j;
    Packet op;
    op.ver=ver;op.typeID=typeID;

    if (binary_packet[*idx]-'0') // length type ID is 1 // we know how many subpackets there is
    {
        *idx+=1;
        char subpacket_sz_bits[12]={'\0'};
        for (j = 0; j < 11; j++)
            subpacket_sz_bits[j] = binary_packet[*idx+j];
        *idx+=11;

        int subpacket_sz = bin2dec(subpacket_sz_bits);

        op.subpackets = (Packet*)malloc(sizeof(Packet)*subpacket_sz);
        op.subpackets_sz = subpacket_sz;

        int newidx=0;
        int literal;
        for (size_t k = 0; k < subpacket_sz; k++)
        {
            char ver_bits[4]={'\0'},typeID_bits[4]={'\0'};

            for (j = 0; j < 3; j++) ver_bits[j] = binary_packet[*idx+j];
            *idx+=3;
            for (j = 0; j < 3; j++) typeID_bits[j] = binary_packet[*idx+j];
            *idx+=3;
            int versub = bin2dec(ver_bits), typeIDsub = bin2dec(typeID_bits);

            if (typeIDsub==4)
                op.subpackets[k] = parseLiteral(binary_packet,idx,versub,typeIDsub);
            else
                op.subpackets[k] = parseOperator(binary_packet,idx,versub,typeIDsub);  
        }

    }
    else // length type ID is 0 // need to know how many subpackets there is
    {
        *idx+=1;
        char subpacket_sz_bits[16]={'\0'};
        for (j = 0; j < 15; j++)
            subpacket_sz_bits[j] = binary_packet[*idx+j];
        *idx+=15;
        int subpacket_sz = bin2dec(subpacket_sz_bits);
        int tempidx = *idx;
        int subpacket_count=0;

        while (*idx<tempidx+subpacket_sz)  
        {
            char ver_bits[4]={'\0'},typeID_bits[4]={'\0'};
            for (j = 0; j < 3; j++) ver_bits[j] = binary_packet[*idx+j];
            *idx+=3;
            for (j = 0; j < 3; j++) typeID_bits[j] = binary_packet[*idx+j];
            *idx+=3;
            int versub = bin2dec(ver_bits), typeIDsub = bin2dec(typeID_bits);
            if(!versub && !typeIDsub) break;
            subpacket_count++;
            if (typeIDsub==4)
                parseLiteral(binary_packet,idx,versub,typeIDsub);
            else 
                parseOperator(binary_packet,idx,versub,typeIDsub);
        }

        *idx = tempidx;
        size_t k;
        op.subpackets = (Packet*)malloc(sizeof(Packet)*subpacket_count);
        op.subpackets_sz = subpacket_count;
        for (k=0; k<subpacket_count;k++)  
        {
            char ver_bits[4]={'\0'},typeID_bits[4]={'\0'};

            for (j = 0; j < 3; j++) ver_bits[j] = binary_packet[*idx+j];
            *idx+=3;
            for (j = 0; j < 3; j++) typeID_bits[j] = binary_packet[*idx+j];
            *idx+=3;
            int versub = bin2dec(ver_bits), typeIDsub = bin2dec(typeID_bits);

            if (typeIDsub==4)
                op.subpackets[k] = parseLiteral(binary_packet,idx,versub,typeIDsub); 
            else
                op.subpackets[k] = parseOperator(binary_packet,idx,versub,typeIDsub);
        }
        
    }

    switch (op.typeID)
    {
    case 0:
        op.literal = subpacketSum(op.subpackets_sz,op.subpackets);
        break;
    case 1:
        op.literal = subpacketProd(op.subpackets_sz,op.subpackets);
        break;
    case 2:
        op.literal = subpacketMin(op.subpackets_sz,op.subpackets);
        break;
    case 3:
        op.literal = subpacketMax(op.subpackets_sz,op.subpackets);
        break;
    case 5: //GT
        op.literal = op.subpackets[0].literal > op.subpackets[1].literal;
        break;
    case 6: //LT
        op.literal = op.subpackets[0].literal < op.subpackets[1].literal;
        break;
    case 7: //EQ
        op.literal = op.subpackets[0].literal == op.subpackets[1].literal;
        break;
    default:
        op.literal = 0;
        break;
    }
 
    return op;
}

void parsePacket(char *binary_packet)
{
    char ver_bits[4]={'\0'}, typeID_bits[4]={'\0'};
    int i,j;

    for (i = 0; i < 3; i++) ver_bits[i] = binary_packet[i];
    for (; i < 6; i++) typeID_bits[i-3] = binary_packet[i];

    int ver = bin2dec(ver_bits), typeID = bin2dec(typeID_bits);

    if (typeID != 4)
        pkts[pkts_sz]=parseOperator(binary_packet,&i,ver,typeID);
    else
        pkts[pkts_sz]=parseLiteral(binary_packet,&i,ver,typeID);

    pkts_sz++;
    if (i<strlen(binary_packet)-1)
    {
        for (j = 0; j < strlen(binary_packet)-i; j++) //check if there are more packets to parse
            if (binary_packet[i+j]!='0') break;

        if(j==strlen(binary_packet)-i) return;
        
        char subpackt[strlen(binary_packet)-i+1];
        for (j = 0; j < strlen(binary_packet)-i; j++)
            subpackt[j] = binary_packet[j+i];
        subpackt[j]='\0';
        parsePacket(subpackt);
    }
    return;
}

void printSubpackets(Packet p, int level)
{
    for (size_t i = 0; i < p.subpackets_sz; i++)
    {
        for (size_t j = 0; j < level; j++) printf("\t");
        printf("ver:%d typeID:%d ",p.subpackets[i].ver,p.subpackets[i].typeID);
        if (p.subpackets[i].typeID==4) printf("literal:%lld\n",p.subpackets[i].literal);
        else 
        {
            printf("\n");
            printSubpackets(p.subpackets[i],level+1);
        }
    }
    return;
}

void printPackets()
{
    for (size_t i = 0; i < pkts_sz; i++)
    {
        printf("ver:%d typeID:%d\n",pkts[i].ver,pkts[i].typeID);
        if (pkts[i].typeID!=4)
            printSubpackets(pkts[i],1);
        else
            printf("literal: %lld",pkts[i].literal);

        printf("\n");
    }
    return;
}

void subpacketVersionSum(Packet p,int *s)
{
    for (size_t i = 0; i < p.subpackets_sz; i++)
    {
        *s+=p.subpackets[i].ver;
        if (p.subpackets[i].typeID!=4) subpacketVersionSum(p.subpackets[i],s);
    }
    return;
}

void getVersionSum(int *s)
{
    for (size_t i = 0; i < pkts_sz; i++)
    {
        *s+=pkts[i].ver;
        if (pkts[i].typeID!=4) subpacketVersionSum(pkts[i],s);
    }
    return;
}

void freeSubpacket(Packet p)
{
    for (size_t i = 0; i < p.subpackets_sz; i++) if (p.subpackets[i].typeID!=4) freeSubpacket(p.subpackets[i]);
    if(p.subpackets!=NULL) free(p.subpackets);
    return; 
}

void freePackets()
{
    for (size_t i = 0; i < pkts_sz; i++) if (pkts[i].typeID!=4) freeSubpacket(pkts[i]);
}

void part1()
{
    FILE *f;

    f = fopen(INPUT_FILE,"r");
    char transmission_line[LINE_CAP];
    fscanf(f,"%s",transmission_line);

    char *binary_packet = hex2bin(transmission_line);

    parsePacket(binary_packet);

    int version_number_sum = 0;
    getVersionSum(&version_number_sum);

    printf("Part 1: %d\n", version_number_sum);
    return;
}

void part2()
{
    FILE *f;

    f = fopen(INPUT_FILE,"r");
    char transmission_line[LINE_CAP];
    fscanf(f,"%s",transmission_line);

    char *binary_packet = hex2bin(transmission_line);

    parsePacket(binary_packet);

    printf("Part 2: %lld\n",pkts[0].literal);
    return;
}

int main()
{
    part1();
    part2();
    freePackets();
    return 0;
}