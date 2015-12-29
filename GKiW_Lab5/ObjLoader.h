#pragma once

struct SFace {
        int v[3];
        int n[3];
        int t[3];
};

GLuint LoadObj(string file);