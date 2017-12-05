import React, { Component } from 'react'
import Radium from 'radium'

const styles = {
  root: {
  },
  content: {
    margin: '150px 0',
  },
  title: {
    fontFamily: "'Oswald', sans-serif",
    fontSize: 36,
    fontWeight: 'bold',
    marginBottom: 20,
  },
  smallDesc: {
    fontSize: 16,
    color: '#4c4c4c',
  },
}

class Home extends Component {
  state = {}

  render() {
    return (
      <div style={styles.root}>
        <div style={styles.content}>
          <div style={styles.title}>JARVIS Home Security</div>
          <div style={styles.smallDesc}>Intelligent solutions for your safety</div>
        </div>
      </div>
    )
  }
}

export default Radium(Home)
