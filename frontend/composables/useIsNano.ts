export const useIsNano = () => {
    const isNano = useState<Boolean>(
        'nanoOrShift',
        () => true
    )

    const setIsNano = () => {
        isNano.value = !isNano.value
    }

    return {
        isNano,
        setIsNano
    }
}