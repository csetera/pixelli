# Pixelli Web Application

vue.js and Vuetify Web application for accessing and controlling a Pixelli LED matrix.

## Project setup

```
# yarn
yarn

# npm
npm install
```

### Compiles and hot-reloads for development

There are a number of modes available for development.  At the moment, those modes control the endpoint used for API calls.

* `dev` - The default Vite development setup.  API calls will not function.
* `api-json-serve` - Vite development mode that uses [vite-plugin-simple-json-server](https://socket.dev/npm/package/vite-plugin-simple-json-server) to serve up static JSON responses for API calls.  These calls are serviced by the standard Vite server listening on `http://localhost:3000`.
* `api-pixelli` - Vite development mode that references the API hosted at `http://pixelli.local`
* `api-pixelli_mock` - Vite development mode that references the API hosted at `http://pixelli_mock.local`

In addition, there are also Visual Studio Code launch configurations that will invoke these startup modes and launch a Chrome browser for developing in the associated mode.

### Compiles and minifies for production

```
# yarn
yarn build

# npm
npm run build
```

### Lints and fixes files

```
# yarn
yarn lint

# npm
npm run lint
```

### Customize configuration

See [Configuration Reference](https://vitejs.dev/config/).

## Dependencies
* [vite-plugin-simple-json-server](https://socket.dev/npm/package/vite-plugin-simple-json-server)
* [Vuetify](https://next.vuetifyjs.com/en/)
* [vue-concurrency](https://vue-concurrency.netlify.app/)
* [Vue Router](https://router.vuejs.org/)
* [VueUse](https://vueuse.org/)

