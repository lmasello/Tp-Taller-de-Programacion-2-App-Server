API REST App Server
=============================

Para que los diferentes clientes se puedan conectar y comunicar con el servidor de canciones de *Music.io*, éste debe brindar una interfaz para la comunicación. Para el desarrollo de esta interfaz se utilizó un protocolo REST (Restful API), donde se definieron las formas en que el cliente enviaba las solicitudes y el servidor enviaba las respuestas de las mismas. 

.. note:: 
	Todo pedido debe contener el parámetro **token** con el token de la sesión correspondiente. De faltar estos campos o ser incorrectos, el servidor responderá con el código HTTP 401 (*UNAUTHORIZED*).


Canciones
---------------------------------------------------------------------------------------------------------------

- Obtener cancion:  ``GET`` a ``/songs/<song_id>``

- Agregar canción: ``POST`` a ``/songs``
	+ *nombre_canción* - nombre real en el perfil
	+ *duración* - duración de la canción
	+ *artista* - nombre del artista de la canción
	+ *album* - nombre del album de la canción