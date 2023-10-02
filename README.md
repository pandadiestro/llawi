# Llawi

*yet another CLI password manager*


## Building

`(ES)`

Si tienes una [`Bourne-based shell`](https://en.wikipedia.org/wiki/Shell_script#Typical_POSIX_scripting_languages) compatible con Unix, simplemente ejecuta `build.sh`, el script debería crear un directorio "build" con un ejecutable en él. Aún no existe un método de instalación oficial multiplataforma...

Si no tienes ninguna shell compatible, tendrás que compilarlo tú mismo con un compilador cualquiera de C; si usa `gcc`, por ejemplo, el comando de compilación sería:

```sh
gcc -Isrc/include ./src/app.c
```

El mismo conjunto de variables debería funcionar en la mayoría de los compiladores.

`(EN)`

If you have a [`Bourne shell`](https://en.wikipedia.org/wiki/Shell_script#Typical_POSIX_scripting_languages) Unix compatible shell then just run `build.sh`, it should create a "build" directory with an executable on it. There is no official install method, yet...

If you dont have such shell you will have to compile it yourself with a c compiler, if you use `gcc`, e.g., the compiling command would be like:

```sh
gcc -Isrc/include ./src/app.c
```

The same set of variables should work on most compilers.

## The pass home

`(ES)`

Debido a que Llawi almacena localmente tus contraseñas cifradas, necesita buscar un directorio determinado donde hacer esto. El directorio se llama `pass_home`. Tú puedes configurar tu propio `pass_home` como una variable de entorno o cambiar el valor predeterminado del mismo en `./src/include/config.h`.

`(EN)`

Since Llawi locally stores your encrypted passwords it needs to search for a certain directory, this is called the `pass_home`. You can set your own `pass_home` as an environment variable or change the default at `./src/include/config.h`.

```sh
export pass_home="$path"
```

## The key

`(ES)`

Debes crear una llave persona única de 13 caracteres que nunca puedas olvidar, esta llave será la clave más imporante de la ejecución del programa.

`(EN)`

You have to create a personal, unique 13-characters long key, this will be the most imporant piece of the subsequent llawi processes.

## Usage

`(ES)`

El comando básico es;

```sh
./build/llawi-build-0-1.out gen [Name] --key [key]
```
Esto genera una nueva contraseña aleatoria que se almacena en el directorio "`pass_home`".

Toma en cuenta que, en este ejemplo, usamos "`./build/llawi-build-0-1.out`" como ejecutable porque ese es el resultado estándar para sistemas basados en UNIX, si tu sistema no es compatible con el script de instalación, como en el caso de Windows y sistema operativos relacionados, entonces usa como comando el binario que hayas producido.

Una vez que ya generaste la contraseña, puedes obtenerla con:

```sh
./build/llawi-build-0-1.out get [Name] --key [key]
```

Y debería retornar la contraseña.

Llawi se diseñó con la abilidad en mente de ser ejecutado como parte de una cadena de comandos con otros programas como [xclip](https://github.com/astrand/xclip).

Por lo que incluso si el output del programs tiene más que solo la contraseña, puedes simplemente redirigir esta misma.

```sh
./build/llawi-build-0-1.out get [Name] --key [key] | xclip
```

Esto es gracias a que los decoradores y visuales son enviados al `stderr` en lugar de a `stdout`, por lo que puedes incluso matar al conejo con:

```sh
./build/llawi-build-0-1.out get [Name] --key [key] 2>/dev/null
```

`(EN)`

The basic command is:

```sh
./build/llawi-build-0-1.out gen [Name] --key [key]
```

It will generate a new random password which will be stored at your `pass_home` directory.

Take in consideration that in this example we use "`./build/llawi-build-0-1.out`" because that is the standard unix build output, if you use, for instance, Windows-based operative systems, and you compiled llawi yourself you should use whatever name you ouputed the binary to in the full calling.

To get the generated password you can run:

```sh
./build/llawi-build-0-1.out get [Name] --key [key]
```

And it should return the password.

Llawi is designed with the ability in mind to be ran as input for another programs (like [xclip](https://github.com/astrand/xclip)). So even though there's more stuff in the output than just the password you can just pipe it.

```sh
./build/llawi-build-0-1.out get [Name] --key [key] | xclip
```

This is thanks to the fact that the visual decorators are printed to `stderr` rather than to `stdout`, so you can even go further and kill the bunny with:

```sh
./build/llawi-build-0-1.out get [Name] --key [key] 2>/dev/null
```

