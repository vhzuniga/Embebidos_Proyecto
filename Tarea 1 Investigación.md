

![Logo

Description automatically generated with low confidence](![Aspose Words 9b9d1b8a-a954-4f44-a75c-b9000a47b610 001](https://github.com/user-attachments/assets/a8924059-6a71-4273-b640-a47174aad158))<a name="page1"></a>**ESCUELA SUPERIOR POLITÉCNICA DEL LITORAL**

**FACULTAD DE INGENIERÍA MECÁNICA Y CIENCIAS DE LA PRODUCCIÓN**





**Sistema de Riego Aqua Smart**

**Sistemas Embebidos**



**Estudiante:**

**Victor Hugo Zuñiga Quesada**








**Enero –2025**




**Introducción**

El sistema de riego automatizado AquaSmart surge como una solución tecnológica innovadora diseñada para abordar la problemática del desperdicio de agua en actividades de riego, tanto en jardines como en aplicaciones agrícolas. En un contexto donde la agricultura consume aproximadamente el 70% del agua dulce a nivel mundial, se hace imprescindible optimizar su uso para promover la sostenibilidad y enfrentar los desafíos del cambio climático.

Este proyecto tiene como objetivo principal desarrollar un sistema inteligente que combine sensores, microcontroladores y conectividad remota para automatizar el cuidado de jardines y áreas agrícolas. Entre sus metas específicas se encuentran:

- Maximizar la eficiencia en el uso del agua, reduciendo el desperdicio mediante un riego preciso basado en las necesidades específicas del suelo y las plantas.
- Proporcionar comodidad y control a los usuarios a través de una aplicación móvil que permita monitorear en tiempo real las condiciones ambientales y del suelo.
- Contribuir al uso sostenible de los recursos hídricos, promoviendo un modelo de riego responsable y eficiente.

**Alcance y Limitaciones**

El proyecto AquaSmart tiene como objetivo la creación de un sistema de riego automatizado e inteligente que se adapte a las necesidades tanto de jardines como de pequeños campos agrícolas. Este sistema se basa en el uso de sensores de humedad del suelo y un microcontrolador (ESP32), que permite gestionar el suministro de agua de manera eficiente y en tiempo real. Entre las funcionalidades principales se incluyen:

![](Aspose.Words.9b9d1b8a-a954-4f44-a75c-b9000a47b610.002.png)

*Ilustración 1: Agua dulce en el mundo*

- **Automatización del riego**: Activación y desactivación automática del sistema según los niveles de humedad detectados.
- **Monitoreo remoto**: Visualización de las condiciones del suelo y del entorno a través de una aplicación móvil conectada por WiFi.
- **Control manual**: Opciones para activar o desactivar manualmente la bomba de agua desde la aplicación móvil.

**Limitaciones**
Si bien AquaSmart ofrece una solución eficiente y automatizada, es importante señalar las siguientes limitaciones del sistema:

1. **Monitoreo limitado**: El sistema no incluye sensores avanzados para medir parámetros adicionales como nutrientes del suelo, salinidad o calidad del agua.
1. **Dependencia de conexión WiFi**: La funcionalidad remota requiere una red WiFi estable, lo que podría limitar su uso en zonas rurales con conectividad limitada.
1. **Predicción meteorológica básica**: No integra análisis climático avanzado, lo que podría limitar la optimización del riego en función de las condiciones meteorológicas futuras.
1. **Escalabilidad restringida**: Está diseñado para jardines y aplicaciones agrícolas de menor escala, no siendo ideal para grandes extensiones de cultivo.






**Diagrama de Contexto**

![](Aspose.Words.9b9d1b8a-a954-4f44-a75c-b9000a47b610.003.png)

**Diagrama de Bloques del Diseño**

![Diagrama

Descripción generada automáticamente](Aspose.Words.9b9d1b8a-a954-4f44-a75c-b9000a47b610.004.png)

**Diagrama de Software o Máquina de Estados**

![Diagrama

Descripción generada automáticamente](Aspose.Words.9b9d1b8a-a954-4f44-a75c-b9000a47b610.005.png)








**Diseño de Interfaces**

![Diagrama

Descripción generada automáticamente con confianza baja](Aspose.Words.9b9d1b8a-a954-4f44-a75c-b9000a47b610.006.png)

**Alternativas de Diseño**

Durante el desarrollo del sistema de riego automatizado AquaSmart, se evaluaron diversas alternativas tecnológicas y de implementación para alcanzar los objetivos del proyecto. Estas son las principales opciones consideradas y las razones detrás de las decisiones adoptadas:

1. **Sensores de Humedad**:
- **Alternativa 1**: Sensor capacitivo de humedad y temperatura del suelo V1,2. Ofrecen mediciones más precisas y son menos propensos a la corrosión.
- **Alternativa 2**: Sensores de humedad resistivos. Son económicos, pero más susceptibles a daños por exposición prolongada a la humedad.
- **Decisión**: Se optó por sensores capacitivos V,12 debido a su durabilidad y precisión, a pesar de su mayor costo, ya que proporcionan datos más confiables a largo plazo.
1. **Microcontrolador**
- **Alternativa 1**: ESP32. Proporciona conectividad WiFi y capacidades de procesamiento adecuadas para el control de sensores y la comunicación con la aplicación móvil.
- **Alternativa 2**: Arduino Uno. Simple y más económico, pero carece de conectividad inalámbrica nativa.
- **Decisión**: Se eligió el ESP32 debido a su conectividad WiFi-integrada, que permite el monitoreo remoto en tiempo real, eliminando la necesidad de componentes adicionales.
1. **Métodos de Activación del Riego**
- **Alternativa 1**: Activación automática basada únicamente en la humedad del suelo.
- **Alternativa 2**: Activación híbrida que combina parámetros de humedad y control manual desde la aplicación móvil.
- **Decisión**: La opción híbrida fue seleccionada para brindar flexibilidad al usuario, permitiendo ajustes manuales cuando sea necesario. 

**Plan de Prueba y Validación**

Para garantizar la funcionalidad, precisión y fiabilidad del sistema, se estableció un plan de pruebas sistemáticas que incluye los siguientes aspectos:

1. **Pruebas de Sensores**:
- **Pruebas de precisión**: Comparar las mediciones de los sensores de humedad del suelo con datos obtenidos por dispositivos calibrados en laboratorio.
- **Durabilidad**: Verificar la resistencia de los sensores a la humedad y al desgaste en condiciones prolongadas.
1. **Pruebas de Comunicación**:
- **Estabilidad del WiFi**: Evaluar la capacidad del sistema para mantener una conexión estable entre el ESP32 y la aplicación móvil.
- **Latencia**: Medir el tiempo de respuesta entre el envío de comandos desde la aplicación y la ejecución en el sistema.
1. **Pruebas de Automatización del Riego**:
- **Activación automática**: Confirmar que el sistema inicia y detiene el riego correctamente en función de los niveles de humedad predeterminados.
- **Riego manual**: Verificar que el usuario puede activar y desactivar el sistema manualmente desde la aplicación móvil.
1. **Validación de la Aplicación Móvil**:
- **Interfaz de usuario**: Asegurarse de que las funcionalidades sean intuitivas y accesibles.

2

