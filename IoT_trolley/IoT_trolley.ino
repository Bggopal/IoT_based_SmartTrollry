#include<WiFi.h>
#include<WiFiClient.h>
#include<WebServer.h>
#include<LiquidCrystal_I2C.h>
#include<Wire.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);

const char* ssid = "Nokia 6";//Replace with your network SSID
const char* password = "05111510";//Replace with your network password

WebServer server(80);

//String page = "";
char input[12];
int count = 0;


int a;
int p1=0,p2=0,p3=0,p4=0;
int c1=0,c2=0,c3=0,c4=0;

double total = 0;
int count_prod = 0;
void setup()
{
  pinMode(15,INPUT);
  pinMode(2,OUTPUT);
  pinMode(4,OUTPUT);
  //pinMode(D4,OUTPUT);
 
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  //Wire.begin(D2, D1);
  lcd.begin(20,4);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("     WELCOME TO");
  lcd.setCursor(0, 1);
  lcd.print("   SMART CART       ");

  delay(2000);

  lcd.clear();

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
  lcd.setCursor(0, 0);
  lcd.print("WiFi Connecting...  ");
  Serial.println("WiFi Connecting...  ");
  }
  Serial.print(WiFi.localIP());
  lcd.setCursor(0, 0);
  lcd.print("WiFi Connected");
  lcd.setCursor(0, 1);
  lcd.print(WiFi.localIP());
  delay(1000);

  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");  Serial.println(WiFi.localIP());
 
  lcd.setCursor(0, 0);
  lcd.print(" PLZ ADD ITEMS     ");
  lcd.setCursor(0, 1);
  lcd.print("    TO CART          ");

/*server.on("/", []()
  {
    page = "<html><head><title>E Cart using IoT</title></head><style type=\"text/css\">";
    page += "table{border-collapse: collapse;}th {background-color:  #3498db ;color: white;}table,td {border: 4px solid black;font-size: x-large;";
    page += "text-align:center;border-style: groove;border-color: rgb(255,0,0);}</style><body><center>";
    page += "<h1>Smart Shopping Cart using IoT</h1><br><br><table style=\"width: 1200px;height: 450px;\"><tr>";
    page += "<th>ITEMS</th><th>QUANTITY</th><th>COST</th></tr><tr><td>Biscuit</td><td>"+String(p1)+"</td><td>"+String(c1)+"</td></tr>";
    page += "<tr><td>Soap</td><td>"+String(p2)+"</td><td>"+String(c2)+"</td></tr><tr><td>Rice(1KG)</td><td>"+String(p3)+"</td><td>"+String(c3)+"</td>";
    page += "</tr><tr><td>Tea(50g)</td><td>"+String(p4)+"</td><td>"+String(c4)+"</td></tr><tr><th>Grand Total</th><th>"+String(count_prod)+"</th><th>"+String(total)+"</th>";
    page += "</tr></table><br><input type=\"button\" name=\"Pay Now\" value=\"Pay Now\" style=\"width: 200px;height: 50px\"></center></body></html>, page)";
  });*/
  server.on("/",handle_onconnect);
  server.begin();
  
}

void loop()
{
  int a=digitalRead(15);
  if (Serial.available())
  {
    count = 0;
    while (Serial.available() && count < 12)
    {
      input[count] = Serial.read();
      count++;
      delay(5);
    }
    if (count == 12)
    {
      if ((strncmp(input, "14004AB1658A", 12) == 0) && (a == 1))
      {
        lcd.setCursor(0, 3);
        lcd.print("Biscuit Added       ");
        lcd.setCursor(0, 4);
        lcd.print("Price(Rs):35.00      ");
        p1++;
        digitalWrite(4,HIGH);
        delay(2000);
        total = total + 35.00;
        count_prod++;
        digitalWrite(4,LOW);
        lcd.clear();
      }
      else if ((strncmp(input, "14004AB1658A", 12) == 0) && (a == 0))
      {
        if(p1>0)
        {
        lcd.clear();
        lcd.setCursor(0, 3);
        lcd.print("Biscuit Removed!!!        ");
        //digitalWrite(D4,HIGH);
        delay(2000);
        p1--;
        total = total - 35.00;
        count_prod--;
        lcd.clear();
        //digitalWrite(D4,LOW);
        }
        else
        {
        lcd.clear();
        lcd.setCursor(0, 3);
        lcd.print("Not in cart!!!        ");
        //digitalWrite(4,HIGH);
        delay(2000);
        //digitalWrite(D4,LOW);
        lcd.clear();
        }
      }
      else if ((strncmp(input, "14004A2CC8BA", 12) == 0) && (a == 1))
      {
        lcd.setCursor(0, 3);
        lcd.print("Soap Added          ");
        lcd.setCursor(0, 4);
        lcd.print("Price(Rs):38.00         ");
        total = total + 38.00;
        digitalWrite(4,HIGH);
        delay(2000);
        p2++;
        count_prod++;
        digitalWrite(4,LOW);
        lcd.clear();
      }
      else if ((strncmp(input, "14004A2CC8BA", 12) == 0) && (a == 0))
      {
         if(p2>0)
        {
        lcd.clear();
        lcd.setCursor(0, 3);
        lcd.print("Soap Removed!!!        ");
        //digitalWrite(D4,HIGH);
        delay(2000);
        p2--;
        total = total - 38.00;
        count_prod--;
        lcd.clear();
        //digitalWrite(D4,LOW);
        }
        else
        {
        lcd.clear();
        lcd.setCursor(0, 3);
        lcd.print("Not in cart!!!        ");
        //digitalWrite(D4,HIGH);
        delay(2000);
        lcd.clear();
        //digitalWrite(D4,LOW);
        }
      }
      else if ((strncmp(input, "140049B7FC16", 12) == 0) && (a == 1))
      {
        lcd.setCursor(0, 3);
        lcd.print("Rice(1KG) Added       ");
        lcd.setCursor(0, 4);
        lcd.print("Price(Rs):55.00      ");
        total = total + 55.00;
        digitalWrite(4,HIGH);
        delay(2000);
        count_prod++;
        p3++;
        lcd.clear();
        digitalWrite(4,LOW);
      }
      else if ((strncmp(input, "140049B7FC16", 12) == 0) && (a==0))
      {
        if(p3>0)
        {
        lcd.clear();
        lcd.setCursor(0, 3);
        lcd.print("Rice(1KG) Removed!!!        ");
        //digitalWrite(D4,HIGH);
        delay(2000);
        total = total - 55.00;
        p3--;
        count_prod--;
        lcd.clear();
        //digitalWrite(D4,LOW);
        }
        else
        {
        lcd.clear();
        lcd.setCursor(0, 3);
        lcd.print("Not in cart!!!        ");
        //digitalWrite(D4,HIGH);
        delay(2000);
        lcd.clear();
        //digitalWrite(D4,LOW);
        }
      }
      else if ((strncmp(input, "14004AD147C8", 12) == 0) && (a == 1))
      {
        lcd.setCursor(0, 3);
        lcd.print("Tea(50g) Added            ");
        lcd.setCursor(0, 4);
        lcd.print("Price(Rs):45.00        ");
        total = total + 45.00;
        count_prod++;
        digitalWrite(4,HIGH);
        p4++;
        delay(2000);
        lcd.clear();
        digitalWrite(4,LOW);
      }
      else if ((strncmp(input, "14004AD147C8", 12) == 0) && (a == 0))
      {
        if(p4>0)
        {
        lcd.clear();
        total = total - 45.00;
        lcd.setCursor(0, 3);
        count_prod--;
        p4--;
        lcd.print("Tea(50g) Removed!!!        ");
        //digitalWrite(D4,HIGH);
        delay(2000);
        lcd.clear();
        //digitalWrite(D4,LOW);
        }
        else
        {
        lcd.clear();
        lcd.setCursor(0, 3);
        lcd.print("Not in cart!!!        ");
        //digitalWrite(D4,HIGH);
        delay(2000);
        lcd.clear();
        //digitalWrite(D4,LOW);
        }
      }
      else if (strncmp(input, "140049FC8223", 12) == 0)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Total Prod:");
        lcd.setCursor(11, 0);
        lcd.print(count_prod);
        lcd.setCursor(0, 1);
        lcd.print("Price:");
        lcd.setCursor(6, 1);
        lcd.print(total);
       
        digitalWrite(2,HIGH);
        delay(5000);

        lcd.clear();
        //digitalWrite(D5,LOW);
        lcd.setCursor(0, 0);
        lcd.print("   Thank you        ");
        lcd.setCursor(0, 1);
        lcd.print("  for Shopping        ");
        digitalWrite(2,LOW);
        c1=c2=c3=c4=0;
        p1=p2=p3=p4=0;
      }
    }
    c1=p1*35.00;
    c2=p2*38.00;
    c3=p3*55.00;
    c4=p4*45.00;
  }
server.handleClient();
}

void handle_onconnect()
{
  server.send(200, "text/html", SendHTML()); 
}

String SendHTML()
{
  String ptr = "<html><head><title>E Cart using IoT</title></head><style type=\"text/css\">";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="table{border-collapse: collapse;}th {background-color:  #3498db ;color: white;}table,td {border: 4px solid black;font-size: x-large";
  ptr +="text-align:center;border-style: groove;border-color: rgb(255,0,0);}</style><body><center>";
  ptr +="<h2>Smart Shopping Cart using IoT</h2><br><br><table style=\"width: 1200px;height: 450px;\"><tr>";;
  ptr +="<th>ITEMS</th><th>QUANTITY</th><th>COST</th></tr><tr><td>Biscuit</td><td>"+String(p1)+"</td><td>"+String(c1)+"</td></tr>";
  ptr +="<tr><td>Soap</td><td>"+String(p2)+"</td><td>"+String(c2)+"</td></tr><tr><td>Rice(1KG)</td><td>"+String(p3)+"</td><td>"+String(c3)+"</td>";
  ptr +="</tr><tr><td>Tea(50g)</td><td>"+String(p4)+"</td><td>"+String(c4)+"</td></tr><tr><th>Grand Total</th><th>"+String(count_prod)+"</th><th>"+String(total)+"</th>";
  ptr +="</tr></table><br><input type=\"button\" name=\"Pay Now\" value=\"Pay Now\" style=\"width: 200px;height: 50px\"></center></body></html>";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  //ptr +="<h1>E Cart using IoT</h1>\n";
  //ptr +="<h3>Using AP(STA) Mode</h3>\n";
  
  /* if(led1stat)
  {ptr +="<p>LED1 Status: ON</p><a class=\"button button-off\" href=\"/led1off\">OFF</a>\n";}
  else
  {ptr +="<p>LED1 Status: OFF</p><a class=\"button button-on\" href=\"/led1on\">ON</a>\n";}

  if(led2stat)
  {ptr +="<p>LED2 Status: ON</p><a class=\"button button-off\" href=\"/led2off\">OFF</a>\n";}
  else
  {ptr +="<p>LED2 Status: OFF</p><a class=\"button button-on\" href=\"/led2on\">ON</a>\n";}

  ptr +="</body>\n";
  ptr +="</html>\n";*/
  return ptr;
}
