#version 410 core

layout(location=0) in vec3 vPosition;
layout(location=1) in vec3 vNormal;
layout(location=2) in vec2 vTexCoords;

out vec3 fNormal;
out vec4 fPosEye;
out vec2 fTexCoords;
out vec4 fragPosLightSpace;
//out

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform	mat3 normalMatrix;
uniform mat4 lightSpaceTrMatrix;

uniform float flow;

#define wavesNr (10)

float phases[wavesNr] = float[](1.0f, 0.5f, 0.3f, 0.7f, 0.2f, 0.8f, 0.4f, 0.6f, 0.1f, 0.9f);
float amplitudes[wavesNr] = float[](0.5f, 0.45f, 0.4f, 0.35f, 0.3f, 0.25f, 0.2f, 0.15f, 0.1f, 0.05f);
float freqs[wavesNr] = float[](0.05f, 0.08f, 0.1f, 0.12f, 0.15f, 0.18f, 0.2f, 0.25f, 0.3f, 0.35f);


float waveSin(float var, float amplitude, float phase, float flow, float freq) {
    return amplitude * sin(var * phase + flow * freq);
}

float waveCos(float var, float amplitude, float phase, float flow, float freq) {
    return amplitude * phase * cos(var * phase + flow * freq);
}

void main()
{
    //compute eye space coordinates
    fragPosLightSpace = lightSpaceTrMatrix * model * vec4(vPosition, 1.0f);
    fPosEye = view * model * vec4(vPosition, 1.0f);

    float sinPos = waveSin(vPosition.x, amplitudes[0], phases[0], flow, freqs[0]);
    float deriv = waveCos(vPosition.x, amplitudes[0], phases[0], flow, freqs[0]);

    float sumOfSines = 0, sumOfDerivs = 0;
    for(int i = 0; i < wavesNr; i++){
        sumOfSines += waveSin(vPosition.x, amplitudes[i], phases[i], flow, freqs[i]);
        sumOfDerivs += waveCos(vPosition.x, amplitudes[i], phases[i], flow, freqs[i]);
    }

    vec3 updatedVPosition = vPosition;
    updatedVPosition.y += sumOfSines;

    vec3 updatedVNormal = vNormal;
    updatedVNormal = cross(
        normalize(vec3(0.0f, 0.0f, 1.0f)),
        normalize(vec3(1.0f, sumOfDerivs, 0.0f))
    );
//    fNormal = normalize(vec3(1.0f, 0.0f, waveCos(vPosition.x, amplitudes[0], phases[0], flow, freqs[0])));
//    fNormal = normalize(updatedVNormal);
    fNormal = normalize(normalMatrix * normalize(updatedVNormal));
//    fNormal = vec3(1.0f, 0.0f, waveCos(vPosition.x, aplitudes[0], phases[0], flow, freqs[0]));

    fTexCoords = vTexCoords;
    gl_Position = projection * view * model * vec4(updatedVPosition, 1.0f);
}
