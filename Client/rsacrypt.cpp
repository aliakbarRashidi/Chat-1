#include "rsacrypt.h"

RSACrypt::RSACrypt()
{
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());

    p_simple = 0;
    q_simple = 0;
    d = 0;
    e = 0;
    f = 0;
    module = 0;
}

void RSACrypt::generationKeys()
{
    d =0;

    do
    {
        SimpleNumber(p_simple, 0);
        SimpleNumber(q_simple, 1);

        module = p_simple*q_simple;
    } while(module<1500);

    f = (p_simple-1) * (q_simple-1);

    for (;;)
    {
        e = qrand() % 150 + 2;
        if (SimpleNumber(e, 2) && e < f && (NOD(e, f) == 1))
            break;
    }

    while ((d * e) % f != 1  )
        d += 1;
}

bool RSACrypt::SimpleNumber(int &n, int t)
{

    if (t==0)
        n = qrand() % 75;
    else if (t==1)
        n = qrand() % 75 + 75;
    else
        n = qrand() % 150;

    if (n < 2)
        SimpleNumber(n, t);

    for (int j = 2; j * j <= n; ++j)
        if (n % j == 0)
            SimpleNumber(n, t);

    return true;
}


int RSACrypt::NOD(int p, int q)
{
    while (p && q)
        if (p >= q)
            p %= q;
        else
            q %= p;

    return p | q;
}

void RSACrypt::encodeText(QString text)
{
    QString EncodeText = text;
    int EnTextSize = text.size();
    int EncodeInt[EnTextSize];

    QString tmpText;
    for(int i=0;i<EnTextSize;i++){
        EncodeInt[i]=modExp(EncodeText[i].unicode(),e,module);
        tmpText.append(QString::number(EncodeInt[i])+" ");
    }
}

void RSACrypt::decodeText(QString text)
{
    QStringList DecryptText = text.split(" ");
    int DecTextSize=DecryptText.size()-1;
    int DecryptInt[DecTextSize];

    QString normalText;
    for(int i=0;i<DecTextSize;i++){
        DecryptInt[i]=DecryptText[i].toInt();
        DecryptInt[i]=modExp(DecryptInt[i],d,module);
        normalText.append(QChar(DecryptInt[i]));
    }
}


int RSACrypt::modExp(long long base, long long exp, long long module){

    if(exp==0)
        return 1;

    if(exp%2==0)
    {
        long long res=modExp(base, exp/2, module);
        return (res*res)%module;
    }
    else
    {
        long long res=modExp(base ,exp-1, module);
        return ((base%module)*res)%module;
    }
}

int RSACrypt::getE()
{
    return e;
}

int RSACrypt::getModule()
{
    return module;
}

int RSACrypt::getD()
{
    return d;
}