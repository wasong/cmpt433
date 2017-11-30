import React, { Component } from 'react'
import Radium from 'radium'

import { Link } from 'react-router-dom'
import AppBar from 'material-ui/AppBar'
import RoundedButton from 'components/Button/RoundedButton'

const styles = {
  title: {
    color: '#333',
    fontFamily: "'Oswald', sans-serif",
    fontSize: 16,
  },
  appBar: {
    backgroundColor: 'none',
  },
  iconStyleRight: {
    display: 'flex',
    margin: 0,
    alignItems: 'center',
  },
}

class NavBar extends Component {
  state = {}

  render() {
    return (
      <AppBar
        title="J A R V I S"
        showMenuIconButton={false}
        style={styles.appBar}
        titleStyle={styles.title}
        iconStyleRight={styles.iconStyleRight}
        iconElementRight={(
          <div>
            <Link to="/"><RoundedButton label="Home" /></Link>
            <Link to="/dashboard"><RoundedButton label="Dashboard" /></Link>
            <Link to="/webcam"><RoundedButton label="Webcam" /></Link>
          </div>
        )}
      />
    )
  }
}

export default Radium(NavBar)
