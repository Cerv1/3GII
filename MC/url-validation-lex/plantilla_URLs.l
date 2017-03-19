      /* -------Sección de Declaraciones------- */

%{
#include <stdio.h>

int n_urls;
void escribir_datos(int d1);
%}

      /* -------Sección de Alias------- */

range_ip                   (([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])\.){3}([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])
range_port                 ([0-9]{1,4}|[1-5][0-9]{4}|6[0-4][0-9]{3}|65[0-4][0-9]{2}|655[0-2][0-9]|6553[0-5])
protocolo                  ((https?|ftp):\/\/)
cabecera_web               (www8?)
ip                         ({range_ip})(\:{range_port})?\/
body_url                   ([^\-\." "][-a-zA-Z0-9@:%._\+~#=]{2,256})
end_url                    ([a-z\.]{2,30})
directory                  (\/[a-zA-Z0-9$%\?\#\@_\.\+!\*\\(\),;:@&=-]{2,30}|%[0-9a-f]{2})
port_url                   ([^\:]:{range_port})

%%

      /* -------Sección de Reglas------- */

{protocolo}?{cabecera_web}{body_url}{end_url}{port_url}?{directory}                                                        {n_urls++;}
{protocolo}?{cabecera_web}{body_url}{end_url}{port_url}?{directory}?                                                      {n_urls++;}
{protocolo}{cabecera_web}?{body_url}{end_url}{port_url}?{directory}                                                        {n_urls++;}
{protocolo}{cabecera_web}?{body_url}{end_url}{port_url}{directory}?                                                        {n_urls++;}
{protocolo}{cabecera_web}?{body_url}{end_url}{port_url}?{directory}?{directory}?{directory}?\/?    {n_urls++;}
{protocolo}?{cabecera_web}{body_url}{end_url}{port_url}?{directory}?{directory}?{directory}?\/?    {n_urls++;}
{protocolo}{ip}                                                                                                                                                                 {n_urls++;}
{protocolo}?localhost{port_url}{directory}?{directory}?                                                                                    {n_urls++;}
{protocolo}?localhost{directory}?{directory}?                                                                                                       {n_urls++;}

%%

      /* -------Sección de Procedimientos------- */

int main(int argc, char *argv[]){

  if(argc == 2){
    yyin = fopen(argv[1],"rt");
    if(yyin == NULL){
      printf("El fichero %s no se puede abrir\n", argv[1]);
      exit(-1);
    }
  }
  else yyin=stdin;

  n_urls = 0;
  yylex();
  escribir_datos(n_urls);
  return 0;
}

void escribir_datos(int d1){
  printf("Número de URLs encontradas: %i",d1);
}
