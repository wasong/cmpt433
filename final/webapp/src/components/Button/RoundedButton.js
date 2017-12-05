import React from 'react'
import RaisedButton from 'material-ui/RaisedButton'
import Radium from 'radium'

const styles = {
  borderRadius: 50,
  boxShadow: 'none',
}

const RoundedButton = props => (
  <RaisedButton
    disableTouchRipple
    buttonStyle={styles}
    style={{ ...styles, margin: '0 5px' }}
    overlayStyle={styles}
    {...props}
  />
)

export default Radium(RoundedButton)
