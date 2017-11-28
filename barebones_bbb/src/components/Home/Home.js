import React, { Component } from 'react'
import { Link } from 'react-router-dom'
import Radium from 'radium'

import RoundedButton from 'components/Button/RoundedButton'

const styles = {
  root: {
    marginTop: 150,
    padding: '0 60px',
  },
  title: {
    fontFamily: "'Oswald', sans-serif",
    fontSize: 50,
    fontWeight: 'bold',
    margin: '10px 0',
  },
}

class Home extends Component {
  state = {}

  render() {
    return (
      <div style={styles.root}>
        <div style={styles.title}>Secure Home by Jarvis</div>
        <Link to="/gallery"><RoundedButton label="Gallery" /></Link>
      </div>
    )
  }
}

export default Radium(Home)
