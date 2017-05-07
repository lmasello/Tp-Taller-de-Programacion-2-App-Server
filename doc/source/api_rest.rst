API REST App Server
=============================

Para que los diferentes clientes se puedan conectar y comunicar con el servidor de canciones de *Music.io*, éste debe brindar una interfaz para la comunicación. Para el desarrollo de esta interfaz se utilizó un protocolo REST (Restful API), donde se definieron las formas en que el cliente enviaba las solicitudes y el servidor enviaba las respuestas de las mismas. 

.. note:: 
	Todo pedido debe contener el parámetro **token** con el token de la sesión correspondiente. De faltar estos campos o ser incorrectos, el servidor responderá con el código HTTP 403 (*FORBIDDEN*).


Canciones
---------------------------------------------------------------------------------------------------------------

- Obtener cancion:  ``GET`` a ``/songs/<song_id>``

Usuarios
---------------------------------------------------------------------------------------------------------------

- Validación de usuarios:  ``GET`` a ``/users/<user_id>``