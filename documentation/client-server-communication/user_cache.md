# Introduction

Users do not have to sign into the client application each and every time it is started. After login, a cache file is created and maintained so as to enable automatic sign-in.

This cache file is automatically changed after the user resets their password.

The cache file is NOT stored in plain text, so as to protect the user.

# Affine Transformation

Cached sign-in uses affine transformation to prevent the storage of plain text credentials.

Later, this MAY be moved to a plain-text storage of the password hash. 
