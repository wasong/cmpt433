import React from 'react'
import PropTypes from 'prop-types'
import Helmet from 'react-helmet'
import { ApolloProvider, ApolloClient, createNetworkInterface } from 'react-apollo'
import { Provider } from 'react-redux'
import { BrowserRouter as Router, browserHistory } from 'react-router-dom'
import MuiThemeProvider from 'material-ui/styles/MuiThemeProvider'
import { StyleRoot } from 'radium'

import Routes from './routes'

// Base stylesheets
import './styles/normalize.css'
import './styles/app.css'

// Setup Apollo client
const createClient = () => (
  new ApolloClient({
    networkInterface: createNetworkInterface({
      uri: 'ADD_CONNECTION_HERE',
    }),
  })
)

function App(props) {
  return (
    <ApolloProvider client={createClient()}>
      <Provider store={props.store}>
        <div>
          <Helmet
            titleTemplate="%s | Some Boilerplate"
            meta={[
              { charset: 'utf-8' },
              {
                'http-equiv': 'X-UA-Compatible',
                content: 'IE=edge',
              },
              {
                name: 'viewport',
                content: 'width=device-width, initial-scale=1',
              },
            ]}
          />
          <MuiThemeProvider>
            <StyleRoot>
              <Router history={browserHistory}>
                <Routes />
              </Router>
            </StyleRoot>
          </MuiThemeProvider>
        </div>
      </Provider>
    </ApolloProvider>
  )
}

App.propTypes = {
  store: PropTypes.object.isRequired, // eslint-disable-line
}

export default App
